// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief транспонирование матрицы
 *
 * @param A матрица
 * @param result результат транспонирования
 * @return int 0 - SUCCESS, 1 - матрица не существует
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (s21_matrix_check(A) && result) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
    res = 0;
  } else {
    res = 1;
  }
  return res;
}
