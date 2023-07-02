// created by pizpotli
#include "s21_matrix.h"

/**
 * @brief очищает память (free)
 *
 * @param A матрица
 */
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix) {
      if (A->rows && A->columns) {
        for (int i = 0; i < A->rows; i++) {
          free(A->matrix[i]);
        }
        free(A->matrix);
        A->columns = 0;
        A->rows = 0;
        A->matrix = NULL;
      }
    }
  }
}
