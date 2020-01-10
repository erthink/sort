#ifdef __cplusplus
extern "C" {
#endif

void std_sort_int64(int64_t *array, size_t size);
void std_stable_int64(int64_t *array, size_t size);
void std_sort_int64_gt(int64_t *array, size_t size);
void std_stable_int64_gt(int64_t *array, size_t size);
void std_sort_pint(int **array, size_t size);
void std_stable_pint(int **array, size_t size);

#ifdef __cplusplus
}
#endif
