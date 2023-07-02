// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief вычитает матрицы
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @param result результат вычитания
 * @return int 0 - SUCCESS, 1 - матрица не существует, 2 - стороны не равны
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res;
  if (s21_matrix_check(A) && s21_matrix_check(B) && result) {
    if (s21_matrix_ravnoe(A, B)) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
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
