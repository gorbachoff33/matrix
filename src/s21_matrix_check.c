// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief проверяет чтобы строки и столбцы были больше 0 и матрица != NULL
 *
 * @param A матрица
 * @return int 0 - FAILURE, 1 - SUCCESS
 */
int s21_matrix_check(matrix_t *A) {
  int res = 0;
  if (A == NULL) {
    res = FAILURE;
  } else if (A->columns < 1 || A->rows < 1 || !A->matrix) {
    A->matrix = NULL;
    res = FAILURE;
  } else {
    res = SUCCESS;
  }
  return res;
}

/**
 * @brief проверяет равны ли размеры матриц
 *
 * @param A 1 матрица
 * @param B 2 матрица
 * @return int 0 - FAILURE, 1 - SUCCESS
 */
int s21_matrix_ravnoe(matrix_t *A, matrix_t *B) {
  int res = 0;
  if (A->columns == B->columns && A->rows == B->rows) {
    res = SUCCESS;
  } else {
    res = FAILURE;
  }
  return res;
}
