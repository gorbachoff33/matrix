// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief умножает матрицы друг на друга
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @param result результат умножения
 * @return int 0 - SUCCESS, 1 - матрица не существует, 2 - стороны не равны
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res;
  double tmp = 0;
  if (s21_matrix_check(A) && s21_matrix_check(B) && result) {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          tmp = 0;
          for (int n = 0; n < B->rows; n++) {
            tmp = tmp + A->matrix[i][n] * B->matrix[n][j];
          }
          result->matrix[i][j] = tmp;
        }
      }
      res = 0;
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}
