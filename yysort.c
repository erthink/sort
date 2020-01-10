#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifndef __has_builtin
#define __has_builtin(x) (0)
#endif

#ifndef likely
#if (defined(__GNUC__) || __has_builtin(__builtin_expect)) &&                  \
    !defined(__COVERITY__)
#define likely(cond) __builtin_expect(!!(cond), 1)
#else
#define likely(x) (x)
#endif
#endif /* likely */

#ifndef unlikely
#if (defined(__GNUC__) || __has_builtin(__builtin_expect)) &&                  \
    !defined(__COVERITY__)
#define unlikely(cond) __builtin_expect(!!(cond), 0)
#else
#define unlikely(x) (x)
#endif
#endif /* unlikely */

#ifndef __unreachable
#if __GNUC_PREREQ(4, 5) || __has_builtin(__builtin_unreachable)
#define __unreachable() __builtin_unreachable()
#elif defined(_MSC_VER)
#define __unreachable() __assume(0)
#else
#define __unreachable()                                                        \
  do {                                                                         \
  } while (0)
#endif
#endif /* __unreachable */

/*----------------------------------------------------------------------------*/

#define YYSORT_ORDERED(CMP, a, b) (!CMP(b, a))

#define YYSORT_CMP_SWAP(TYPE, CMP, a, b)                                       \
  do {                                                                         \
    const TYPE swap_tmp = (a);                                                 \
    const _Bool swap_ordered = YYSORT_ORDERED(CMP, swap_tmp, b);               \
    (a) = swap_ordered ? swap_tmp : (b);                                       \
    (b) = swap_ordered ? (b) : swap_tmp;                                       \
  } while (0)

#define YYSORT_BITONIC_2(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
  } while (0)

#define YYSORT_BITONIC_3(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
  } while (0)

#define YYSORT_BITONIC_4(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
  } while (0)

#define YYSORT_BITONIC_5(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
  } while (0)

#define YYSORT_BITONIC_6(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
  } while (0)

#define YYSORT_BITONIC_7(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
  } while (0)

#define YYSORT_BITONIC_8(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
  } while (0)

#define YYSORT_BITONIC_9(TYPE, CMP, begin)                                     \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
  } while (0)

#define YYSORT_BITONIC_10(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
  } while (0)

#define YYSORT_BITONIC_11(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
  } while (0)

#define YYSORT_BITONIC_12(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[11]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
  } while (0)

#define YYSORT_BITONIC_13(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[11]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[11]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
  } while (0)

#define YYSORT_BITONIC_14(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[11]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[12], begin[13]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[13]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
  } while (0)

#define YYSORT_BITONIC_15(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[11]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[12], begin[13]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[12], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[14]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[13], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[13]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
  } while (0)

#define YYSORT_BITONIC_16(TYPE, CMP, begin)                                    \
  do {                                                                         \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[1]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[11]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[12], begin[13]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[14], begin[15]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[12], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[3]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[13], begin[15]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[15]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[0], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[14]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[15]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[13], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[11]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[2]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[4], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[1], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[13]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[14]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[2], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[13]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[12]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[10], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[5]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[9]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[3], begin[4]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[5], begin[6]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[7], begin[8]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[9], begin[10]);                           \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[11], begin[12]);                          \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[6], begin[7]);                            \
    YYSORT_CMP_SWAP(TYPE, CMP, begin[8], begin[9]);                            \
  } while (0)

/*----------------------------------------------------------------------------*/

#define YYSORT_SWAP(TYPE, a, b)                                                \
  do {                                                                         \
    const TYPE swap_tmp = (a);                                                 \
    (a) = (b);                                                                 \
    (b) = swap_tmp;                                                            \
  } while (0)

#define YYSORT_PUSH(low, high)                                                 \
  do {                                                                         \
    top->lo = (low);                                                           \
    top->hi = (high);                                                          \
    ++top;                                                                     \
  } while (0)

#define YYSORT_POP(low, high)                                                  \
  do {                                                                         \
    --top;                                                                     \
    low = top->lo;                                                             \
    high = top->hi;                                                            \
  } while (0)

#define YYSORT_IMPL(EXPECT_LOW_CARDINALITY_OR_PRESORTED, PREFIX, TYPE, CMP)    \
                                                                               \
  static __inline void PREFIX##_inner(TYPE *begin, const size_t num) {         \
    switch (num) {                                                             \
    default:                                                                   \
      __unreachable();                                                         \
    case 0:                                                                    \
    case 1:                                                                    \
      break;                                                                   \
    case 2:                                                                    \
      YYSORT_BITONIC_2(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 3:                                                                    \
      YYSORT_BITONIC_3(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 4:                                                                    \
      YYSORT_BITONIC_4(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 5:                                                                    \
      YYSORT_BITONIC_5(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 6:                                                                    \
      YYSORT_BITONIC_6(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 7:                                                                    \
      YYSORT_BITONIC_7(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 8:                                                                    \
      YYSORT_BITONIC_8(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 9:                                                                    \
      YYSORT_BITONIC_9(TYPE, CMP, begin);                                      \
      break;                                                                   \
    case 10:                                                                   \
      YYSORT_BITONIC_10(TYPE, CMP, begin);                                     \
      break;                                                                   \
    case 11:                                                                   \
      YYSORT_BITONIC_11(TYPE, CMP, begin);                                     \
      break;                                                                   \
    case 12:                                                                   \
      YYSORT_BITONIC_12(TYPE, CMP, begin);                                     \
      break;                                                                   \
    case 13:                                                                   \
      YYSORT_BITONIC_13(TYPE, CMP, begin);                                     \
      break;                                                                   \
    case 14:                                                                   \
      YYSORT_BITONIC_14(TYPE, CMP, begin);                                     \
      break;                                                                   \
    case 15:                                                                   \
      YYSORT_BITONIC_15(TYPE, CMP, begin);                                     \
      break;                                                                   \
    case 16:                                                                   \
      YYSORT_BITONIC_16(TYPE, CMP, begin);                                     \
      break;                                                                   \
    }                                                                          \
  }                                                                            \
                                                                               \
  typedef struct {                                                             \
    TYPE *lo, *hi;                                                             \
  } PREFIX##_stack;                                                            \
                                                                               \
  static _Bool PREFIX##_is_sorted(const TYPE *begin, const TYPE *last) {       \
    while (++begin <= last)                                                    \
      if (!YYSORT_ORDERED(CMP, begin[-1], begin[0]))                           \
        return false;                                                          \
    return true;                                                               \
  }                                                                            \
                                                                               \
  static __inline void PREFIX##_impl(TYPE *const begin, TYPE *const end) {     \
    PREFIX##_stack stack[sizeof(int) * CHAR_BIT], *top = stack;                \
                                                                               \
    TYPE *hi = end - 1;                                                        \
    TYPE *lo = begin;                                                          \
    while (true) {                                                             \
      const ptrdiff_t len = hi - lo;                                           \
      if (len < 16) {                                                          \
        PREFIX##_inner(lo, len + 1);                                           \
        if (unlikely(top == stack))                                            \
          return;                                                              \
        YYSORT_POP(lo, hi);                                                    \
        continue;                                                              \
      }                                                                        \
                                                                               \
      TYPE *mid = lo + (len >> 1);                                             \
      YYSORT_CMP_SWAP(TYPE, CMP, *lo, *mid);                                   \
      YYSORT_CMP_SWAP(TYPE, CMP, *mid, *hi);                                   \
      YYSORT_CMP_SWAP(TYPE, CMP, *lo, *mid);                                   \
                                                                               \
      TYPE *right = hi - 1;                                                    \
      TYPE *left = lo + 1;                                                     \
      while (1) {                                                              \
        while (CMP(*left, *mid))                                               \
          ++left;                                                              \
        while (CMP(*mid, *right))                                              \
          --right;                                                             \
        if (unlikely(left > right)) {                                          \
          if (EXPECT_LOW_CARDINALITY_OR_PRESORTED) {                           \
            if (PREFIX##_is_sorted(lo, right))                                 \
              lo = right + 1;                                                  \
            if (PREFIX##_is_sorted(left, hi))                                  \
              hi = left;                                                       \
          }                                                                    \
          break;                                                               \
        }                                                                      \
        YYSORT_SWAP(TYPE, *left, *right);                                      \
        mid = (mid == left) ? right : (mid == right) ? left : mid;             \
        ++left;                                                                \
        --right;                                                               \
      }                                                                        \
                                                                               \
      if (right - lo > hi - left) {                                            \
        YYSORT_PUSH(lo, right);                                                \
        lo = left;                                                             \
      } else {                                                                 \
        YYSORT_PUSH(left, hi);                                                 \
        hi = right;                                                            \
      }                                                                        \
    }                                                                          \
  }

/*----------------------------------------------------------------------------*/

#define CMP_LT(a, b) ((a) < (b))
#define CMP_SB(a, b) (((a) - (b)) < 0)

YYSORT_IMPL(false, yysort1_int64, int64_t, CMP_LT)
YYSORT_IMPL(true, yysort2_int64, int64_t, CMP_LT)
YYSORT_IMPL(false, yysort1_int64_sb, int64_t, CMP_SB)
YYSORT_IMPL(true, yysort2_int64_sb, int64_t, CMP_SB)

void yysort1_int64(int64_t *array, size_t size) {
  yysort1_int64_impl(array, array + size);
}

void yysort2_int64(int64_t *array, size_t size) {
  yysort2_int64_impl(array, array + size);
}

void yysort1_int64_sb(int64_t *array, size_t size) {
  yysort1_int64_sb_impl(array, array + size);
}

void yysort2_int64_sb(int64_t *array, size_t size) {
  yysort2_int64_sb_impl(array, array + size);
}
