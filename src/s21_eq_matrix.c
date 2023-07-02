// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief сравнивает матрицы
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @return int 0 - FAILURE, 1 - SUCCESS
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  double tmp = 0;
  if (s21_matrix_check(A) && s21_matrix_check(B) && s21_matrix_ravnoe(A, B)) {
    for (int i = 0; i < A->rows && res != FAILURE; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        tmp = fabs(A->matrix[i][j]) - fabs(B->matrix[i][j]);
        if (fabs(tmp) > s21_EPS) {
          res = FAILURE;
        } else {
          res = SUCCESS;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}
