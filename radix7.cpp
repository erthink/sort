/* This file was copied from the https://github.com/travisdowns/sort-bench
 * with minor changes.
 *
 * For more information about this source code see origin blog post
 * https://travisdowns.github.io/blog/2019/05/22/sorting.html */

#include "extra.h"

#include <algorithm>
#include <array>
#include <assert.h>
#include <memory>
#include <string.h>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

const size_t RADIX_BITS = 8;
const size_t RADIX_SIZE = (size_t)1 << RADIX_BITS;
const size_t RADIX_LEVELS = (63 / RADIX_BITS) + 1;
const uint64_t RADIX_MASK = RADIX_SIZE - 1;

using freq_array_type = size_t[RADIX_LEVELS][RADIX_SIZE];

#if 0
#include "hedley.h"
// never inline just to make it show up easily in profiles (inlining this
// lengthly function doesn't really help anyways)
HEDLEY_NEVER_INLINE
#endif
static void count_frequency(int64_t *a, size_t count, freq_array_type freqs) {
  for (size_t i = 0; i < count; i++) {
    uint64_t value = static_cast<uint64_t>(a[i]);
    for (size_t pass = 0; pass < RADIX_LEVELS; pass++) {
      freqs[pass][value & RADIX_MASK]++;
      value >>= RADIX_BITS;
    }
  }
}

/**
 * Determine if the frequencies for a given level are "trivial".
 *
 * Frequencies are trivial if only a single frequency has non-zero
 * occurrences. In that case, the radix step just acts as a copy so we can
 * skip it.
 */
static bool is_trivial(size_t freqs[RADIX_SIZE], size_t count) {
  for (size_t i = 0; i < RADIX_SIZE; i++) {
    auto freq = freqs[i];
    if (freq != 0) {
      return freq == count;
    }
  }
  assert(count == 0); // we only get here if count was zero
  return true;
}

void radix_sort7_int64(int64_t *array, size_t count) {
  std::unique_ptr<int64_t[]> queue_area(new int64_t[count]);
  // huge_unique_ptr<uint64_t[]> queue_area = make_huge_array<uint64_t>(count,
  // false);

  freq_array_type freqs = {};
  count_frequency(array, count, freqs);

  int64_t *from = array, *to = queue_area.get();

  for (size_t pass = 0; pass < RADIX_LEVELS; pass++) {

    if (is_trivial(freqs[pass], count)) {
      // this pass would do nothing, just skip it
      continue;
    }

    int shift = pass * RADIX_BITS;

    // array of pointers to the current position in each queue, which we set up
    // based on the known final sizes of each queue (i.e., "tighly packed")
    int64_t *queue_ptrs[RADIX_SIZE], *next = to;
    for (size_t i = 0; i < RADIX_SIZE; i++) {
      queue_ptrs[i] = next;
      next += freqs[pass][i];
    }

    // copy each element into the appropriate queue based on the current
    // RADIX_BITS sized "digit" within it
    for (size_t i = 0; i < count; i++) {
      size_t value = from[i];
      size_t index = (value >> shift) & RADIX_MASK;
      *queue_ptrs[index]++ = value;
      __builtin_prefetch(queue_ptrs[index] + 1);
    }

    // swap from and to areas
    std::swap(from, to);
  }

  // because of the last swap, the "from" area has the sorted payload: if it's
  // not the original array "a", do a final copy
  if (from != array) {
    std::copy(from, from + count, array);
  }
}
