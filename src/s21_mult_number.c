// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief умножает матрицу на число с точкой
 *
 * @param A матрица
 * @param number число с точкой
 * @param result результат умножения
 * @return int 0 - SUCCESS, 1 - матрица не существует
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res;
  // printf("mult:%lf\n", A->matrix[0][0]);
  if (s21_matrix_check(A) && result) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    res = 0;
  } else {
    res = 1;
  }
  return res;
}
