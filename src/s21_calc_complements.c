// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief вычисляет алгебраическое дополнение
 *
 * @param A матрица
 * @param result результат
 * @return int 0 - SUCCESS, 1 - матрица не существует, 2 - стороны не равны
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->rows != A->columns || A->rows <= 1) {
    if (A->rows <= 1) {
      res = 1;
    } else {
      res = 2;
    }
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    matrix_t tmp;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_matrix_minor(A, &tmp, i, j);
        double det = 0;
        s21_determinant(&tmp, &det);
        s21_remove_matrix(&tmp);

        result->matrix[i][j] = pow(-1.0, i + j) * det;
      }
    }
  }
  return res;
}
