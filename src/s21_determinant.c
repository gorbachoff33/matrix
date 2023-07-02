// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief вычисляет определитель
 *
 * @param A матрица
 * @param result результат
 * @return int 0 - SUCCESS, 1 - матрица не существует, 2 - стороны не равны
 */
int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (s21_matrix_check(A) && result != NULL) {
    if (A->columns == A->rows) {
      *result = s21_determ_1(A, A->rows);
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

/**
 * @brief считает определитель
 *
 * @param A матрица
 * @param invert 1 меняет знак, согласно формуле
 * @param tmp записывается матрица с вычеркнутой строкой и столбцом
 * @param rows любая из сторон
 * @return double результат
 */
double s21_determ_1(matrix_t *A, int rows) {
  double result = 0, invert = 1;
  if (rows == 1) {
    result = A->matrix[0][0];
  } else if (rows == 2) {
    result =
        (A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0]);
  } else {
    matrix_t tmp = {0};
    for (int i = 0; i < A->rows; i++) {
      s21_matrix_minor(A, &tmp, 0, i);
      double temp = A->matrix[0][i];
      result = result + (invert * temp * s21_determ_1(&tmp, rows - 1));
      invert = -invert;
      s21_remove_matrix(&tmp);
    }
  }
  return result;
}

/**
 * @brief убирает заданную строку и столбец из матрицы
 *
 * @param A матрица
 * @param result результат после вычеркивания строки и столбца
 * @param i строка которую вычеркнуть
 * @param j столбец который вычеркнуть
 */
void s21_matrix_minor(matrix_t *A, matrix_t *result, int i, int j) {
  int i1 = 0, i2 = 0, j1 = 0, j2 = 0;
  s21_create_matrix(A->rows - 1, A->rows - 1, result);
  for (i1 = 0; i1 < A->rows - 1; i1++) {
    if (i1 == i) {
      i2 = 1;
    }
    j2 = 0;
    for (j1 = 0; j1 < A->rows - 1; j1++) {
      if (j1 == j) {
        j2 = 1;
      }
      result->matrix[i1][j1] = A->matrix[i1 + i2][j1 + j2];
    }
  }
}
