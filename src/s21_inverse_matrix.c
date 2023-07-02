// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief обратная матрица
 *
 * @param A матрица
 * @param result результат
 * @return int 0 - SUCCESS, 1 - матрица не существует, 2 - стороны не равны
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->rows < 1 || !s21_matrix_check(A) || !result) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else {
    double det = 0;
    matrix_t tmp;
    s21_create_matrix(A->columns, A->rows, &tmp);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp.matrix[i][j] = A->matrix[i][j];
      }
    }
    s21_determinant(A, &det);
    if (det == 0) {
      res = 2;
      s21_remove_matrix(&tmp);
    } else {
      if (A->rows > 1 && A->columns > 1) {
        matrix_t tmp2;
        s21_calc_complements(&tmp, &tmp2);
        matrix_t transpon;
        s21_transpose(&tmp2, &transpon);
        s21_mult_number(&transpon, 1.0 / det, result);
        s21_remove_matrix(&transpon);
        s21_remove_matrix(&tmp2);
      } else {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      }
      s21_remove_matrix(&tmp);
    }
  }
  return res;
}
