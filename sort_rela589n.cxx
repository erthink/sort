#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <vector>

using namespace std;

#define SORT_TYPE int64_t

static SORT_TYPE *dont_delete;
static inline void safe_delete(SORT_TYPE *ptr) {
  if (ptr != dont_delete)
    delete[] ptr;
}

static SORT_TYPE *glue(SORT_TYPE *a, SORT_TYPE lenA, SORT_TYPE *b,
                       SORT_TYPE lenB) {
  int lenC = lenA + lenB;
  SORT_TYPE *c = new SORT_TYPE[lenC]; // результирующий массив
  int indx_a = 0;
  int indx_b = 0;
  int i = 0;

  for (; i < lenC; ++i) {
    if (indx_a < lenA) {
      if (indx_b < lenB) { // Оба массива содержат элементы
        c[i] = (a[indx_a] < b[indx_b]) ? a[indx_a++] : b[indx_b++];
        continue;
      } // Элементы есть только в первом
      while (indx_a < lenA)
        c[i++] = a[indx_a++];
    } else // Элементы есть только во втором
      while (indx_b < lenB)
        c[i++] = b[indx_b++];
    break;
  }

  return c;
}

static void glueDelete(SORT_TYPE *&arr, SORT_TYPE *&a, SORT_TYPE lenA,
                       SORT_TYPE *&b, SORT_TYPE lenB) {
  if (lenA == 0) {  // если первый пустой
    safe_delete(a); // высвобождаем от него память
    arr = b; // результирующий будет вторым массивом
    return;
  }
  if (lenB == 0) {  // если второй пустой
    safe_delete(b); // высвобождаем от него память
    arr = a; // результирующий будет вторым массивом
    return;
  }

  SORT_TYPE *copy = glue(a, lenA, b, lenB); // сливаем
  safe_delete(a); // удаляемо ненужные массивы
  safe_delete(b); // удаляемо ненужные массивы
  arr = copy;     // изменяем указатель
}

static void insertionSort(SORT_TYPE *arr, int lo, int hi) {
  for (int i = lo + 1; i <= hi; ++i)
    for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j)
      swap(arr[j - 1], arr[j]);
}

static const int catchUp = 8;

/// works only if arr is pointer assigned by new keyword
static void newGenerationSort(SORT_TYPE *&arr, int len) {
  int localCatchUp =
      min(catchUp, len); // потому что мы не можем пытаться вставлять элемент за
                         // границами массива
  insertionSort(arr, 0,
                localCatchUp -
                    1); // для начала сортируем первые localCatchUp элементов

  if (len <=
      localCatchUp) // на случай если это массив на n <= catchUp элементов
    return;         // а также это база рекурсии

  SORT_TYPE *selection =
      new SORT_TYPE[len << 1]; // то же что и new int[len * 2]
  int left = len - 1; // индекс для хранения новых минимальных элементов
  int right = len; // индекс для хранения новых максимальных элементов

  selection[left--] = arr[0];
  for (int i = 1; i < localCatchUp; ++i) {
    selection[right++] = arr[i];
  }

  int restLen = len >> 1;
  SORT_TYPE *restFirst = new SORT_TYPE[restLen];
  SORT_TYPE *restSecond = new SORT_TYPE[restLen];

  int restFirstLen = 0;
  int restSecondLen = 0;

  for (int i = localCatchUp; i < len; ++i) {

    if (selection[right - localCatchUp] <= arr[i]) {
      selection[right] = arr[i];

      for (int j = right; selection[j - 1] > selection[j]; --j)
        swap(selection[j - 1], selection[j]);

      ++right;
      continue;
    }

    if (selection[left + localCatchUp] >= arr[i]) {
      selection[left] = arr[i];

      for (int j = left; selection[j] >= selection[j + 1]; ++j)
        swap(selection[j], selection[j + 1]);

      --left;
      continue;
    }

    if (i & 1) { // i - непарное
      restFirst[restFirstLen++] = arr[i];
    } else {
      restSecond[restSecondLen++] = arr[i];
    }
  }
  safe_delete(arr);

  int selectionLen = right - left - 1; // просто длина нашей выборки
  SORT_TYPE *copy = glue(selection + left + 1, selectionLen, nullptr,
                         0); // копируем все элементы выборки в новый массив

  delete[] selection; // удаляем массив размером 2 * len элементов и
  selection =
      copy; // вместо него используем ровно столько памяти, сколько нужно

  newGenerationSort(restFirst, restFirstLen);
  newGenerationSort(restSecond, restSecondLen);

  SORT_TYPE *part2;
  int part2Len;
  if (selectionLen < restFirstLen) {
    glueDelete(selection, restFirst, restFirstLen, selection,
               selectionLen); // selection += restFirst
    selectionLen += restFirstLen;

    part2 = restSecond;
    part2Len = restSecondLen;
  } else {
    glueDelete(part2, restFirst, restFirstLen, restSecond,
               restSecondLen); // part2 = restFirst + restSecond
    part2Len = restFirstLen + restSecondLen;
  }

  glueDelete(arr, selection, selectionLen, part2, part2Len);
}

//------------------------------------------------------------------------------

extern "C" void sort_rela589n_int64(int64_t *const array, size_t size) {
  if (size > 1) {
#if 1
    dont_delete = array;
    int64_t *stupid = array;
    newGenerationSort(stupid, size);
    if (stupid != array) {
      memcpy(array, stupid, size * sizeof(int64_t));
      delete[] stupid;
    }
    dont_delete = nullptr;
#else
    int64_t *stupid = new int64_t[size];
    memcpy(stupid, array, size * sizeof(int64_t));
    newGenerationSort(stupid, size);
    memcpy(array, stupid, size * sizeof(int64_t));
    delete[] stupid;
#endif
  }
}
