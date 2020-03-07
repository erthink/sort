#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void std_sort_int64(int64_t *array, size_t size);
void std_stable_int64(int64_t *array, size_t size);
void std_sort_int64_gt(int64_t *array, size_t size);
void std_stable_int64_gt(int64_t *array, size_t size);
void std_sort_pint(int **array, size_t size);
void std_stable_pint(int **array, size_t size);

void yysort1_int64(int64_t *array, size_t size);
void yysort2_int64(int64_t *array, size_t size);
void yysort1_int64_sb(int64_t *array, size_t size);
void yysort2_int64_sb(int64_t *array, size_t size);

void sort_rela589n_int64(int64_t *array, size_t size);
void radix_sort7_int64(int64_t *array, size_t size);

#ifdef __cplusplus
}
#endif
