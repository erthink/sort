/* Copyright (c) 2010-2014 Christopher Swenson. */
/* Copyright (c) 2012 Google Inc. All Rights Reserved. */

#define _XOPEN_SOURCE
#include <sys/time.h>

#define SORT_NAME sorter
#define SORT_TYPE int64_t
#define SORT_CMP(x, y) ((x) - (y))
#include "sort.h"

#undef SORT_TYPE
#undef SORT_CMP
#undef SORT_SWAP

#define SORT_NAME stable
#define SORT_TYPE int *
#define SORT_CMP(x, y) (*(x) - *(y))
#include "sort.h"

#include "extra.h"

/* Used to control the stress test */
#define SEED 42
#define MAXSIZE 42000
#define TESTS 1000

#define RAND_RANGE(__n, __min, __max)                                          \
  (__n) = (__min) + (long)((double)((double)(__max) - (__min) + 1.0) *         \
                           ((__n) / (RAND_MAX + 1.0)))

enum {
  FILL_RANDOM,
  FILL_RNDDUP50,
  FILL_RANDOM2,
  FILL_RANDOM10,
  FILL_MIXED,
  FILL_MIXDUP50,
  FILL_MIXED2,
  FILL_MIXED10,
  FILL_SORTED,
  FILL_SORTED94,
  FILL_REVERSE,
  FILL_REVERSE2,
  FILL_REVERSE10,
  FILL_ALLSAME,
  FILL_SORTED_10,
  FILL_SORTED_100,
  FILL_SORTED_10000,
  FILL_SWAPPED_N2,
  FILL_SWAPPED_N8,
  FILL_EVIL1,
  FILL_EVIL2,
  FILL_LAST_ELEMENT
};

char *test_names[FILL_LAST_ELEMENT] = {
    "random",
    "random 50% duplicates",
    "random two values",
    "random of 0..9",
    "mixed-pattern (1/2 sorted, 1/6 reverse, 1/3 random)",
    "mixed-pattern 50% duplicates",
    "mixed-pattern two values",
    "mixed-pattern of 0..9",
    "sorted",
    "sorted 93.75%",
    "reverse",
    "111......000",
    "999..., 888..., ..., ...000",
    "all same",
    "sorted blocks of length 10",
    "sorted blocks of length 100",
    "sorted blocks of length 10000",
    "swapped size/2 pairs",
    "swapped size/8 pairs",
    "known evil data (odd/even swap)",
    "known evil data (odd/even hi/low swap)"};

/* used for stdlib */
static __inline int simple_cmp(const void *a, const void *b) {
  const int64_t da = *((const int64_t *)a);
  const int64_t db = *((const int64_t *)b);
  return (da < db) ? -1 : (da == db) ? 0 : 1;
}

static __inline int simple_cmp_reverse(const void *a, const void *b) {
  return simple_cmp(b, a);
}

static __inline double utime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (1000000.0 * t.tv_sec + t.tv_usec);
}

/* helper functions */
int verify(int64_t *dst, const unsigned size) {
  for (unsigned i = 1; i < size; i++) {
    if (dst[i - 1] > dst[i]) {
      printf("Verify failed! at %d", i);
      return 0;
    }
  }
  return 1;
}

static void fill_random(int64_t *dst, const unsigned size) {
  for (unsigned i = 0; i < size; i++)
    dst[i] = lrand48();
}

static void fill_random2(int64_t *dst, const unsigned size) {
  for (unsigned i = 0; i < size; i++)
    dst[i] = lrand48() & 1;
}

static void fill_random10(int64_t *dst, const unsigned size) {
  for (unsigned i = 0; i < size; i++)
    dst[i] = lrand48() % 10;
}

static void make_mixed(int64_t *dst, const unsigned size) {
  const unsigned sorted = size / 2;
  const unsigned reverse = size / 2 / 3;
  qsort(dst, sorted, sizeof(int64_t), simple_cmp);
  qsort(dst + sorted, reverse, sizeof(int64_t), simple_cmp_reverse);
}

static void make_disord6(int64_t *dst, const unsigned size) {
  uint64_t r = dst[0];
  for (int i = size / 16; i >= 0; --i) {
    r = r * UINT64_C(6364136223846793005) + 1;
    const unsigned x = (r >> 29) % size;
    r = r * UINT64_C(6364136223846793005) + 1;
    const unsigned y = (r >> 29) % size;
    int64_t t = dst[x];
    dst[x] = dst[y];
    dst[y] = t;
  }
}

static void fill_same(int64_t *dst, const unsigned size) {
  for (unsigned i = 0; i < size; i++)
    dst[i] = 0;
}

static void fill_dup50(int64_t *dst, const unsigned size) {
  fill_random(dst, size);
  uint64_t r = dst[0];
  for (unsigned i = 0; i < size; i++) {
    r = r * UINT64_C(6364136223846793005) + 1;
    const unsigned x = (r >> 29) % size;
    r = r * UINT64_C(6364136223846793005) + 1;
    const unsigned y = (r >> 29) % size;
    dst[x] = dst[y];
  }
}

static void fill_sorted(int64_t *dst, const unsigned size) {
  for (unsigned i = 0; i < size; i++)
    dst[i] = i;
}

static void fill_reverse(int64_t *dst, const unsigned size) {
  for (unsigned i = 0; i < size; i++)
    dst[size - i] = i;
}

static void fill_sorted_blocks(int64_t *dst, const int size,
                               const int block_size) {
  int i, filled, this_block_size;
  filled = 0;

  for (i = 0; i < size; i += block_size) {
    this_block_size =
        (filled + block_size) < size ? block_size : (size - filled);
    fill_random(dst + filled, this_block_size);
    qsort(dst + filled, this_block_size, sizeof(int64_t), simple_cmp);
    filled += this_block_size;
  }
}

static void fill_swapped(int64_t *dst, const int size, const int swapped_cnt) {
  fill_sorted(dst, size);
  for (unsigned i = 0; i < swapped_cnt; i++) {
    size_t ind1 = lrand48();
    RAND_RANGE(ind1, 0, size);
    size_t ind2 = lrand48();
    RAND_RANGE(ind2, 0, size);
    int64_t tmp = dst[ind1];
    dst[ind1] = dst[ind2];
    dst[ind2] = tmp;
  }
}

static void fill(int64_t *dst, const int size, int type) {
  switch (type) {
  case FILL_RANDOM:
    fill_random(dst, size);
    break;

  case FILL_RNDDUP50:
    fill_dup50(dst, size);
    break;

  case FILL_RANDOM2:
    fill_random2(dst, size);
    break;

  case FILL_RANDOM10:
    fill_random10(dst, size);
    break;

  case FILL_MIXED:
    fill_random(dst, size);
    make_mixed(dst, size);
    break;

  case FILL_MIXDUP50:
    fill_dup50(dst, size);
    make_mixed(dst, size);
    break;

  case FILL_MIXED2:
    fill_random2(dst, size);
    make_mixed(dst, size);
    break;

  case FILL_MIXED10:
    fill_random10(dst, size);
    make_mixed(dst, size);
    break;

  case FILL_SORTED:
    fill_sorted(dst, size);
    break;

  case FILL_SORTED94:
    fill_sorted(dst, size);
    make_disord6(dst, size);
    break;

  case FILL_REVERSE:
    fill_reverse(dst, size);
    break;

  case FILL_REVERSE2:
    fill_random2(dst, size);
    qsort(dst, size, sizeof(int64_t), simple_cmp_reverse);
    break;

  case FILL_REVERSE10:
    fill_random10(dst, size);
    qsort(dst, size, sizeof(int64_t), simple_cmp_reverse);
    break;

  case FILL_ALLSAME:
    fill_same(dst, size);
    break;

  case FILL_SORTED_10:
    fill_sorted_blocks(dst, size, 10);
    break;

  case FILL_SORTED_100:
    fill_sorted_blocks(dst, size, 100);
    break;

  case FILL_SORTED_10000:
    fill_sorted_blocks(dst, size, 10000);
    break;

  case FILL_SWAPPED_N2:
    fill_swapped(dst, size, size / 2);
    break;

  case FILL_SWAPPED_N8:
    fill_swapped(dst, size, size / 8);
    break;

  case FILL_EVIL1:
    for (unsigned i = 0; i < size; i++)
      dst[i] = i ^ 1;
    break;

  case FILL_EVIL2:
    for (unsigned i = 0; i < size; i++)
      dst[i] = (i & 1) ? i : size - i;
    break;

  default:
    abort();
  }
}

#define TEST_STDLIB(name)                                                      \
  do {                                                                         \
    res = 0;                                                                   \
    diff = 0;                                                                  \
    printf("%-29s", "stdlib " #name);                                          \
    for (test = 0; test < sizes_cnt; test++) {                                 \
      int64_t size = sizes[test];                                              \
      fill(dst, size, type);                                                   \
      usec1 = utime();                                                         \
      name(dst, size, sizeof(int64_t), simple_cmp);                            \
      usec2 = utime();                                                         \
      res = verify(dst, size);                                                 \
      if (!res) {                                                              \
        break;                                                                 \
      }                                                                        \
      diff += usec2 - usec1;                                                   \
    }                                                                          \
    printf(" - %s, %10.1f usec\n", res ? "ok" : "FAILED", diff);               \
    fflush(NULL);                                                              \
    if (!res)                                                                  \
      return 0;                                                                \
  } while (0)

#define TEST_SORT_H(name)                                                      \
  do {                                                                         \
    res = 0;                                                                   \
    diff = 0;                                                                  \
    printf("%-29s", "sort.h " #name);                                          \
    for (test = 0; test < sizes_cnt; test++) {                                 \
      int64_t size = sizes[test];                                              \
      fill(dst, size, type);                                                   \
      usec1 = utime();                                                         \
      sorter_##name(dst, size);                                                \
      usec2 = utime();                                                         \
      res = verify(dst, size);                                                 \
      if (!res) {                                                              \
        break;                                                                 \
      }                                                                        \
      diff += usec2 - usec1;                                                   \
    }                                                                          \
    printf(" - %s, %10.1f usec\n", res ? "ok" : "FAILED", diff);               \
    fflush(NULL);                                                              \
    if (!res)                                                                  \
      return 0;                                                                \
  } while (0)

#define TEST_EXTRA_H(name)                                                     \
  do {                                                                         \
    res = 0;                                                                   \
    diff = 0;                                                                  \
    printf("%-29s", "extra.h " #name);                                         \
    for (test = 0; test < sizes_cnt; test++) {                                 \
      int64_t size = sizes[test];                                              \
      fill(dst, size, type);                                                   \
      usec1 = utime();                                                         \
      name(dst, size);                                                         \
      usec2 = utime();                                                         \
      res = verify(dst, size);                                                 \
      if (!res) {                                                              \
        break;                                                                 \
      }                                                                        \
      diff += usec2 - usec1;                                                   \
    }                                                                          \
    printf(" - %s, %10.1f usec\n", res ? "ok" : "FAILED", diff);               \
    fflush(NULL);                                                              \
    if (!res)                                                                  \
      return 0;                                                                \
  } while (0)

int run_tests(int64_t *sizes, int sizes_cnt, int type) {
  int test, res;
  double usec1, usec2, diff;
  int64_t *dst = (int64_t *)malloc(MAXSIZE * sizeof(int64_t));
  printf("-------\nRunning tests with %s:\n", test_names[type]);
  TEST_EXTRA_H(yysort1_int64);
  TEST_EXTRA_H(yysort2_int64);
  // TEST_EXTRA_H(yysort1_int64_sb);
  // TEST_EXTRA_H(yysort2_int64_sb);
  TEST_EXTRA_H(sort_rela589n_int64);

  TEST_SORT_H(tim_sort);
  TEST_SORT_H(quick_sort);
  TEST_EXTRA_H(std_sort_int64);
  TEST_EXTRA_H(std_stable_int64);
  TEST_SORT_H(heap_sort);
  TEST_SORT_H(merge_sort);
  TEST_SORT_H(shell_sort);
  TEST_SORT_H(merge_sort_in_place);
  TEST_SORT_H(grail_sort);
  TEST_SORT_H(sqrt_sort);
  // TEST_SORT_H(rec_stable_sort);
  // TEST_SORT_H(grail_sort_dyn_buffer);

  TEST_STDLIB(qsort);
#if !defined(__linux__) && !defined(__CYGWIN__)
  TEST_STDLIB(heapsort);
  TEST_STDLIB(mergesort);
#endif

  if (MAXSIZE < 10000) {
    TEST_SORT_H(selection_sort);
    TEST_SORT_H(bubble_sort);
    TEST_SORT_H(binary_insertion_sort);
    TEST_SORT_H(bitonic_sort);
  }
  free(dst);
  return 0;
}

/* stability testing functions */
/* cheap hack to keep a copy to compare against */
static int **original;
static int first_original = 0;

/* make a int* array */
void make_intp_array(int **array, int64_t size, int num_values) {
  int64_t i;

  if (first_original == 0) {
    first_original = 1;
    original = malloc(sizeof(int *) * size);
  }

  for (i = 0; i < size; i++) {
    array[i] = original[i] = malloc(sizeof(int));
    *(array[i]) = lrand48() % num_values;
  }
}

/* free all the pointers */
void clean_intp_array(int **array, int64_t size) {
  int64_t i;

  for (i = 0; i < size; i++) {
    free(array[i]);
  }
}

/* find the first instance of an element in an array of pointers */
int64_t find_next(int **array, int64_t start, int64_t last, int value) {
  int64_t i;

  for (i = start; i < last; i++) {
    if (*(array[i]) == value) {
      break;
    }
  }

  return i;
}

/* verify that the given list is stable */
int verify_stable(int **array, int64_t size, int num_values) {
  int value;
  int64_t i = 0;
  int64_t j = 0;

  for (value = 0; value < num_values; value++) {
    while (1) {
      i = find_next(original, i, size, value);

      /* unlikely, but possible */
      if (i == size) {
        break;
      }

      j = find_next(array, j, size, value);

      if (j == size) {
        return 0;
      }

      if (original[i] != array[j]) {
        return 0;
      }

      i++;
      j++;
    }
  }

  return 1;
}

/* Checks that given sort function is stable. */
void check_stable(char *name, void (*sort_fun)(int **arr, size_t size),
                  int size, int num_values) {
  int **array = malloc(sizeof(int *) * size);
  make_intp_array(array, size, num_values);
  sort_fun(array, size);
  printf("%21s -- %s\n", name,
         verify_stable(array, size, num_values) ? "stable" : "UNSTABLE");
  clean_intp_array(array, size);
  free(array);
}

/* Check which sorts are stable. */
void stable_tests() {
  int size = 100000;
  int num_values = 1000;
  check_stable("selection sort", stable_selection_sort, size, num_values);
  check_stable("binary insertion sort", stable_binary_insertion_sort, size,
               num_values);
  check_stable("bubble sort", stable_bubble_sort, size, num_values);
  check_stable("quick sort", stable_quick_sort, size, num_values);
  check_stable("merge sort", stable_merge_sort, size, num_values);
  check_stable("heap sort", stable_heap_sort, size, num_values);
  check_stable("shell sort", stable_shell_sort, size, num_values);
  check_stable("tim sort", stable_tim_sort, size, num_values);
  check_stable("merge (in-place) sort", stable_merge_sort_in_place, size,
               num_values);
  check_stable("grail sort", stable_grail_sort, size, num_values);
  check_stable("sqrt sort", stable_sqrt_sort, size, num_values);
  check_stable("rec stable sort", stable_rec_stable_sort, size, num_values);
  check_stable("grail sort dyn byffer", stable_grail_sort_dyn_buffer, size,
               num_values);
  check_stable("std::sort", std_sort_pint, size, num_values);
  check_stable("std::stable_sort", std_stable_pint, size, num_values);
}

int main(void) {
  int i = 0;
  int64_t sizes[TESTS];
  srand48(SEED);
  // stable_tests();
  fill_random(sizes, TESTS);

  for (i = 0; i < TESTS; i++) {
    RAND_RANGE(sizes[i], 1, MAXSIZE);
  }

  sizes[TESTS - 1] = MAXSIZE;

  for (i = 0; i < FILL_LAST_ELEMENT; i++) {
    int result = run_tests(sizes, TESTS, i);

    if (result) {
      return 1;
    }
  }

  return 0;
}
