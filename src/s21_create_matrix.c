// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief создает матрицу (использует динамическую память)
 *
 * @param rows колличество строк
 * @param columns колличество столбцов
 * @param result готовая матрица заполненная нулями
 * @return int 0 - ОК, 1 - некорректные данные
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (result == NULL || rows < 1 || columns < 1) {
    res = 1;
    result = NULL;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows && res == 0; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        res = 1;
      }
    }
  }
  return res;
}
