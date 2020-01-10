#include <algorithm>
#include <cstdint>

#include "extra.h"

struct lt_int64 {
  bool inline operator()(int64_t a, int64_t b) const { return a < b; }
};

extern "C" void std_sort_int64(int64_t *array, size_t size) {
  std::sort(array, array + size, lt_int64());
}

extern "C" void std_stable_int64(int64_t *array, size_t size) {
  std::stable_sort(array, array + size, lt_int64());
}

struct gt_int64 {
  bool inline operator()(int64_t a, int64_t b) const { return a > b; }
};

extern "C" void std_sort_int64_gt(int64_t *array, size_t size) {
  std::sort(array, array + size, gt_int64());
}

extern "C" void std_stable_int64_gt(int64_t *array, size_t size) {
  std::stable_sort(array, array + size, gt_int64());
}

struct lt_ptr_int {
  bool inline operator()(int *a, int *b) const { return *a < *b; }
};

extern "C" void std_sort_pint(int **array, size_t size) {
  std::sort(array, array + size, lt_ptr_int());
}

extern "C" void std_stable_pint(int **array, size_t size) {
  std::stable_sort(array, array + size, lt_ptr_int());
}
