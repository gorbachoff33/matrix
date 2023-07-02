#include "check.h"
#include "s21_matrix.h"

#define OK 0
#define WRONG_MATRIX 1
#define CALCULATION_ERROR 2

#define SUCCESS 1
#define FAILURE 0

// create_matrix
START_TEST(test_s21_create_matrix_1) {
  matrix_t A;
  int flag = s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(A.rows, 2);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_int_eq(flag, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_2) {
  matrix_t A;
  int flag = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_int_eq(flag, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_3) {
  matrix_t A;
  int flag = s21_create_matrix(0, 3, &A);
  ck_assert_int_eq(flag, WRONG_MATRIX);
}
END_TEST

START_TEST(test_s21_create_matrix_4) {
  matrix_t A;
  int flag = s21_create_matrix(3, -3, &A);
  ck_assert_int_eq(flag, WRONG_MATRIX);
}
END_TEST

// eq_matrix
START_TEST(test_s21_eq_matrix_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.columns; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_2) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 1, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }

  int flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_3) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, SUCCESS);
  B.matrix[2][2] += 0.0000009;
  flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_4) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count + 1.0;
      count = count + 1.0;
    }
  }
  int flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_5) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 3, &B);
  int flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_6) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(-1, 1, &B);
  int flag = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(flag, FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

// sum_matrix
START_TEST(test_s21_sum_matrix_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
      count = count + 1.0;
    }
  }

  int flag = s21_sum_matrix(&A, &B, &D);
  int flag_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(flag, OK);
  ck_assert_int_eq(flag_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 3, &B);

  int flag = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// sub_matrix
START_TEST(test_s21_sub_matrix_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
      count = count + 1.0;
    }
  }

  int flag = s21_sub_matrix(&A, &B, &D);
  int flag_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(flag, OK);
  ck_assert_int_eq(flag_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 3, &B);

  int flag = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_number_1) {
  double number = 2.0;
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = A.matrix[i][j] * number;
      count = count + 1.0;
    }
  }

  int flag = s21_mult_number(&A, number, &C);
  int flag_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(flag, OK);
  ck_assert_int_eq(flag_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

// mult_matrix
START_TEST(test_s21_mult_matrix_1) {
  double count = 1.0;
  double count2 = 3.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_create_matrix(1, 1, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[j][i] = count2;
      count = count + 1.0;
      count2 = count2 - 1.0;
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int k = 0; k < B.rows; k++) {
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  int flag = s21_mult_matrix(&A, &B, &D);
  int flag_eq = s21_eq_matrix(&C, &D);

  ck_assert_int_eq(flag, OK);
  ck_assert_int_eq(flag_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_mult_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(4, 1, &B);
  s21_create_matrix(1, 1, &C);

  int flag = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

// transpose
START_TEST(test_s21_transpose_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[j][i] = count;
      count = count + 1.0;
    }
  }

  int flag = s21_transpose(&A, &C);
  int flag_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(flag, OK);
  ck_assert_int_eq(flag_eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

// calc_complements
START_TEST(test_s21_calc_complements_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int flag = s21_calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], 0);
  ck_assert_int_eq(B.matrix[0][1], 10);
  ck_assert_int_eq(B.matrix[0][2], -20);
  ck_assert_int_eq(B.matrix[1][0], 4);
  ck_assert_int_eq(B.matrix[1][1], -14);
  ck_assert_int_eq(B.matrix[1][2], 8);
  ck_assert_int_eq(B.matrix[2][0], -8);
  ck_assert_int_eq(B.matrix[2][1], -2);
  ck_assert_int_eq(B.matrix[2][2], 4);
  ck_assert_int_eq(flag, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_calc_complements_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;

  int flag = s21_calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], -12);
  ck_assert_int_eq(B.matrix[0][1], 20);
  ck_assert_int_eq(B.matrix[0][2], -2);
  ck_assert_int_eq(B.matrix[1][0], 0);
  ck_assert_int_eq(B.matrix[1][1], 0);
  ck_assert_int_eq(B.matrix[1][2], 0);
  ck_assert_int_eq(B.matrix[2][0], 12);
  ck_assert_int_eq(B.matrix[2][1], -20);
  ck_assert_int_eq(B.matrix[2][2], 2);
  ck_assert_int_eq(flag, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_calc_complements_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 1, &A);

  int flag = s21_calc_complements(&A, &B);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// determinant
START_TEST(test_s21_determinant_1) {
  double count = 1.0;
  double determinant = 0.0;
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      count = count + 1.0;
    }
  }

  int flag = s21_determinant(&A, &determinant);
  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq(determinant, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_2) {
  double determinant = 0.0;
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = 13;
  A.matrix[0][3] = 7;

  A.matrix[1][0] = 5;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 23;
  A.matrix[1][3] = 11;

  A.matrix[2][0] = 13;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 9;
  A.matrix[2][3] = 8;

  A.matrix[3][0] = 20;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = 4;
  A.matrix[3][3] = 7;
  int flag = s21_determinant(&A, &determinant);
  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq(determinant, 596);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_4) {
  double determinant = 0.0;
  matrix_t A;
  s21_create_matrix(3, 1, &A);

  int flag = s21_determinant(&A, &determinant);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_5) {
  double determinant = 0.0;
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 27;

  int flag = s21_determinant(&A, &determinant);
  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq(determinant, 27);
  s21_remove_matrix(&A);
}
END_TEST

// inverse_matrix
START_TEST(test_s21_inverse_matrix_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int flag = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(flag, OK);
  ck_assert_int_eq(B.matrix[0][0], 1);
  ck_assert_int_eq(B.matrix[0][1], -1);
  ck_assert_int_eq(B.matrix[0][2], 1);
  ck_assert_int_eq(B.matrix[1][0], -38);
  ck_assert_int_eq(B.matrix[1][1], 41);
  ck_assert_int_eq(B.matrix[1][2], -34);
  ck_assert_int_eq(B.matrix[2][0], 27);
  ck_assert_int_eq(B.matrix[2][1], -29);
  ck_assert_int_eq(B.matrix[2][2], 24);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;

  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 8;

  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;

  int flag = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);

  int flag = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(flag, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

double s21_floor(double num, int x) {
  int temp1 = num;
  num -= temp1;
  int temp_x = x;
  while (temp_x) {
    num *= 10;
    temp_x--;
  }
  double z = (int)num;
  while (x) {
    z /= 10;
    x--;
  }
  return (double)temp1 + z;
}

START_TEST(s21_create_matrix_1) {
  matrix_t shit1;
  int check = s21_create_matrix(5, 5, &shit1);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t shit1;
  int check = s21_create_matrix(-10, 0, &shit1);
  ck_assert_int_eq(check, WRONG_MATRIX);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(3, 3, &shit1);
  s21_create_matrix(3, 3, &shit2);
  shit1.matrix[0][0] = 2;
  shit1.matrix[0][1] = 5;
  shit1.matrix[0][2] = 7;
  shit1.matrix[1][0] = 6;
  shit1.matrix[1][1] = 3;
  shit1.matrix[1][2] = 4;
  shit1.matrix[2][0] = 5;
  shit1.matrix[2][1] = -2;
  shit1.matrix[2][2] = -3;
  int check = s21_eq_matrix(&shit1, &shit2);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  ck_assert_int_eq(check, FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(3, 3, &shit1);
  s21_create_matrix(3, 3, &shit2);
  int check = s21_eq_matrix(&shit1, &shit2);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  ck_assert_int_eq(check, SUCCESS);
}
END_TEST

START_TEST(s21_sum_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 3, &shit1);
  s21_create_matrix(2, 2, &shit2);
  matrix_t result;
  int check = s21_sum_matrix(&shit1, &shit2, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 2, &shit1);
  s21_create_matrix(2, 2, &shit2);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 1;
  shit1.matrix[1][0] = 1;
  shit1.matrix[1][1] = 1;
  shit2.matrix[0][0] = 1;
  shit2.matrix[0][1] = 1;
  shit2.matrix[1][0] = 1;
  shit2.matrix[1][1] = 1;
  matrix_t sum;
  s21_create_matrix(2, 2, &sum);
  sum.matrix[0][0] = 2;
  sum.matrix[0][1] = 2;
  sum.matrix[1][0] = 2;
  sum.matrix[1][1] = 2;
  matrix_t result;
  int check = s21_sum_matrix(&shit1, &shit2, &result);
  int check2 = s21_eq_matrix(&sum, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_sub_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 3, &shit1);
  s21_create_matrix(2, 2, &shit2);
  matrix_t result;
  int check = s21_sub_matrix(&shit1, &shit2, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 2, &shit1);
  s21_create_matrix(2, 2, &shit2);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 1;
  shit1.matrix[1][0] = 1;
  shit1.matrix[1][1] = 1;
  shit2.matrix[0][0] = 1;
  shit2.matrix[0][1] = 1;
  shit2.matrix[1][0] = 1;
  shit2.matrix[1][1] = 1;
  matrix_t sum;
  s21_create_matrix(2, 2, &sum);
  sum.matrix[0][0] = 0;
  sum.matrix[0][1] = 0;
  sum.matrix[1][0] = 0;
  sum.matrix[1][1] = 0;
  matrix_t result;
  int check = s21_sub_matrix(&shit1, &shit2, &result);
  int check2 = s21_eq_matrix(&sum, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_mult_number_matrix_1) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 2;
  shit1.matrix[0][2] = 3;
  shit1.matrix[1][0] = 0;
  shit1.matrix[1][1] = 4;
  shit1.matrix[1][2] = 2;
  shit1.matrix[2][0] = 2;
  shit1.matrix[2][1] = 3;
  shit1.matrix[2][2] = 4;
  double A = 2;
  matrix_t res;
  s21_create_matrix(3, 3, &res);
  res.matrix[0][0] = 2;
  res.matrix[0][1] = 4;
  res.matrix[0][2] = 6;
  res.matrix[1][0] = 0;
  res.matrix[1][1] = 8;
  res.matrix[1][2] = 4;
  res.matrix[2][0] = 4;
  res.matrix[2][1] = 6;
  res.matrix[2][2] = 8;
  matrix_t result;
  s21_mult_number(&shit1, A, &result);
  int check = s21_eq_matrix(&result, &res);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res);
  ck_assert_int_eq(check, SUCCESS);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 2, &shit1);
  s21_create_matrix(3, 2, &shit2);
  matrix_t result;
  int check = s21_mult_matrix(&shit1, &shit2, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(3, 2, &shit1);
  s21_create_matrix(2, 3, &shit2);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 4;
  shit1.matrix[1][0] = 2;
  shit1.matrix[1][1] = 5;
  shit1.matrix[2][0] = 3;
  shit1.matrix[2][1] = 6;
  shit2.matrix[0][0] = 1;
  shit2.matrix[0][1] = -1;
  shit2.matrix[0][2] = 1;
  shit2.matrix[1][0] = 2;
  shit2.matrix[1][1] = 3;
  shit2.matrix[1][2] = 4;
  matrix_t res;
  s21_create_matrix(3, 3, &res);
  res.matrix[0][0] = 9;
  res.matrix[0][1] = 11;
  res.matrix[0][2] = 17;
  res.matrix[1][0] = 12;
  res.matrix[1][1] = 13;
  res.matrix[1][2] = 22;
  res.matrix[2][0] = 15;
  res.matrix[2][1] = 15;
  res.matrix[2][2] = 27;
  matrix_t result;
  int check = s21_mult_matrix(&shit1, &shit2, &result);
  int check2 = s21_eq_matrix(&res, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_transpose_matrix_1) {
  matrix_t shit1;
  s21_create_matrix(3, 2, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 4;
  shit1.matrix[1][0] = 2;
  shit1.matrix[1][1] = 5;
  shit1.matrix[2][0] = 3;
  shit1.matrix[2][1] = 6;
  matrix_t res;
  s21_create_matrix(2, 3, &res);
  res.matrix[0][0] = 1;
  res.matrix[0][1] = 2;
  res.matrix[0][2] = 3;
  res.matrix[1][0] = 4;
  res.matrix[1][1] = 5;
  res.matrix[1][2] = 6;
  matrix_t result;
  int check = s21_transpose(&shit1, &result);
  int check2 = s21_eq_matrix(&res, &result);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 2;
  shit1.matrix[0][2] = 3;
  shit1.matrix[1][0] = 0;
  shit1.matrix[1][1] = 4;
  shit1.matrix[1][2] = 2;
  shit1.matrix[2][0] = 5;
  shit1.matrix[2][1] = 2;
  shit1.matrix[2][2] = 1;
  matrix_t for_check;
  s21_create_matrix(3, 3, &for_check);
  for_check.matrix[0][0] = 0;
  for_check.matrix[0][1] = 10;
  for_check.matrix[0][2] = -20;
  for_check.matrix[1][0] = 4;
  for_check.matrix[1][1] = -14;
  for_check.matrix[1][2] = 8;
  for_check.matrix[2][0] = -8;
  for_check.matrix[2][1] = -2;
  for_check.matrix[2][2] = 4;
  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);
  int check2 = s21_eq_matrix(&for_check, &result);
  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A;
  s21_create_matrix(3, 1, &A);
  matrix_t result;
  int check = s21_calc_complements(&A, &result);
  s21_remove_matrix(&A);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  double result;
  s21_determinant(&A, &result);
  s21_remove_matrix(&A);
  ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 0;
  double result;
  int check = s21_determinant(&A, &result);
  s21_remove_matrix(&A);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;
  matrix_t result;
  int check = s21_inverse_matrix(&A, &result);
  int check2 = s21_eq_matrix(&result, &B);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      if (s21_floor((B.matrix)[i][j], 7) !=
          s21_floor((result.matrix)[i][j], 7)) {
      }
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 0;
  matrix_t result;
  int check = s21_inverse_matrix(&A, &result);
  s21_remove_matrix(&A);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 2;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = -1;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = 0;
  B.matrix[2][1] = -1;
  B.matrix[2][2] = 1;
  matrix_t result;
  int check = s21_inverse_matrix(&A, &result);
  int check2 = s21_eq_matrix(&result, &B);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      if (s21_floor((B.matrix)[i][j], 7) !=
          s21_floor((result.matrix)[i][j], 7)) {
      }
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 2;
  shit1.matrix[0][2] = 4;
  shit1.matrix[1][0] = 3;
  shit1.matrix[1][1] = 3;
  shit1.matrix[1][2] = 5;
  shit1.matrix[2][0] = 2;
  shit1.matrix[2][1] = 4;
  shit1.matrix[2][2] = 4;
  matrix_t for_check;
  s21_create_matrix(3, 3, &for_check);
  for_check.matrix[0][0] = -8;
  for_check.matrix[0][1] = -2;
  for_check.matrix[0][2] = 6;
  for_check.matrix[1][0] = 8;
  for_check.matrix[1][1] = -4;
  for_check.matrix[1][2] = 0;
  for_check.matrix[2][0] = -2;
  for_check.matrix[2][1] = 7;
  for_check.matrix[2][2] = -3;
  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);
  int check2 = s21_eq_matrix(&for_check, &result);
  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t shit1;
  s21_create_matrix(4, 4, &shit1);
  shit1.matrix[0][0] = 5;
  shit1.matrix[0][1] = 1;
  shit1.matrix[0][2] = 1;
  shit1.matrix[0][3] = 1;
  shit1.matrix[1][0] = 1;
  shit1.matrix[1][1] = 1;
  shit1.matrix[1][2] = 2;
  shit1.matrix[1][3] = 1;
  shit1.matrix[2][0] = 1;
  shit1.matrix[2][1] = 19;
  shit1.matrix[2][2] = 3;
  shit1.matrix[2][3] = 1;
  shit1.matrix[3][0] = 27;
  shit1.matrix[3][1] = 1;
  shit1.matrix[3][2] = 1;
  shit1.matrix[3][3] = 5;
  matrix_t for_check;
  s21_create_matrix(4, 4, &for_check);
  for_check.matrix[0][0] = -158;
  for_check.matrix[0][1] = 22;
  for_check.matrix[0][2] = -396;
  for_check.matrix[0][3] = 928;
  for_check.matrix[1][0] = 64;
  for_check.matrix[1][1] = 12;
  for_check.matrix[1][2] = 20;
  for_check.matrix[1][3] = -352;
  for_check.matrix[2][0] = 4;
  for_check.matrix[2][1] = -14;
  for_check.matrix[2][2] = 16;
  for_check.matrix[2][3] = -22;
  for_check.matrix[3][0] = 18;
  for_check.matrix[3][1] = -4;
  for_check.matrix[3][2] = 72;
  for_check.matrix[3][3] = -158;
  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);
  int check2 = s21_eq_matrix(&for_check, &result);
  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_5) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = -215.5;
  shit1.matrix[0][1] = -23.3;
  shit1.matrix[0][2] = 4;
  shit1.matrix[1][0] = 12.2;
  shit1.matrix[1][1] = 23.3;
  shit1.matrix[1][2] = 32.2;
  shit1.matrix[2][0] = 5;
  shit1.matrix[2][1] = 1;
  shit1.matrix[2][2] = -1.25;
  matrix_t for_check;
  s21_create_matrix(3, 3, &for_check);
  for_check.matrix[0][0] = -61.325;
  for_check.matrix[0][1] = 176.25;
  for_check.matrix[0][2] = -104.3;
  for_check.matrix[1][0] = -25.125;
  for_check.matrix[1][1] = 249.375;
  for_check.matrix[1][2] = 99;
  for_check.matrix[2][0] = -843.46;
  for_check.matrix[2][1] = 6987.9;
  for_check.matrix[2][2] = -4736.89;
  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);
  int check2 = s21_eq_matrix(&for_check, &result);
  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_6) {
  matrix_t shit1;
  s21_create_matrix(2, 2, &shit1);
  shit1.matrix[0][0] = -12551.1;
  shit1.matrix[0][1] = 1035.5;
  shit1.matrix[1][0] = 124.5151;
  shit1.matrix[1][1] = 0;
  matrix_t for_check;
  s21_create_matrix(2, 2, &for_check);
  for_check.matrix[0][0] = 0;
  for_check.matrix[0][1] = -124.5151;
  for_check.matrix[1][0] = -1035.5;
  for_check.matrix[1][1] = -12551.1;
  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);
  int check2 = s21_eq_matrix(&for_check, &result);
  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_7) {
  matrix_t shit1;
  s21_create_matrix(1, 3, &shit1);
  shit1.matrix[0][0] = -12551.1;
  shit1.matrix[0][1] = 1035.5;
  shit1.matrix[0][2] = 124.5151;
  matrix_t for_check;
  s21_create_matrix(2, 2, &for_check);
  for_check.matrix[0][0] = 0;
  for_check.matrix[0][1] = -124.5151;
  for_check.matrix[1][0] = -1035.5;
  for_check.matrix[1][1] = -12551.1;
  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);
  ck_assert_int_eq(check, WRONG_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements_8) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = -1;
  B.matrix[0][1] = 38;
  B.matrix[0][2] = -27;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = -41;
  B.matrix[1][2] = 29;
  B.matrix[2][0] = -1;
  B.matrix[2][1] = 34;
  B.matrix[2][2] = -24;
  matrix_t result;
  int check = s21_calc_complements(&A, &result);
  int check2 = s21_eq_matrix(&result, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(test_s21_check_matrix) {
  matrix_t *A = NULL;
  int flag = s21_matrix_check(A);
  ck_assert_int_eq(flag, FAILURE);
}
END_TEST

START_TEST(test_s21_check_matrix_1) {
  matrix_t A;
  A.matrix = NULL;
  int flag = s21_matrix_check(&A);
  ck_assert_int_eq(flag, FAILURE);
}
END_TEST

Suite *test_func_equal(void) {
  Suite *x;
  x = suite_create("check");

  TCase *s21_create_matrix_case;
  TCase *s21_eq_matrix_case;
  TCase *s21_sum_matrix_case;
  TCase *s21_sub_matrix_case;
  TCase *s21_mult_number_matrix_case;
  TCase *s21_mult_matrix_case;
  TCase *s21_transpose_matrix_case;
  TCase *s21_calc_complements_case;
  TCase *s21_determinant_case;
  TCase *s21_inverse_matrix_case;
  TCase *s21_check_matrix_case;

  s21_create_matrix_case = tcase_create("check_create");
  s21_eq_matrix_case = tcase_create("check_eq");
  s21_sum_matrix_case = tcase_create("check_sum");
  s21_sub_matrix_case = tcase_create("check_sub");
  s21_mult_number_matrix_case = tcase_create("check_mult_number");
  s21_mult_matrix_case = tcase_create("check_mult");
  s21_transpose_matrix_case = tcase_create("check_transpone");
  s21_calc_complements_case = tcase_create("check_calc_complements");
  s21_determinant_case = tcase_create("check_determinant");
  s21_inverse_matrix_case = tcase_create("check_inverse");
  s21_check_matrix_case = tcase_create("check_matrix");

  suite_add_tcase(x, s21_create_matrix_case);
  suite_add_tcase(x, s21_eq_matrix_case);
  suite_add_tcase(x, s21_sum_matrix_case);
  suite_add_tcase(x, s21_sub_matrix_case);
  suite_add_tcase(x, s21_mult_matrix_case);
  suite_add_tcase(x, s21_mult_number_matrix_case);
  suite_add_tcase(x, s21_transpose_matrix_case);
  suite_add_tcase(x, s21_calc_complements_case);
  suite_add_tcase(x, s21_determinant_case);
  suite_add_tcase(x, s21_inverse_matrix_case);
  suite_add_tcase(x, s21_check_matrix_case);

  tcase_add_test(s21_create_matrix_case, s21_create_matrix_1);
  tcase_add_test(s21_create_matrix_case, s21_create_matrix_2);
  tcase_add_test(s21_eq_matrix_case, s21_eq_matrix_1);
  tcase_add_test(s21_eq_matrix_case, s21_eq_matrix_2);
  tcase_add_test(s21_sum_matrix_case, s21_sum_matrix_1);
  tcase_add_test(s21_sum_matrix_case, s21_sum_matrix_2);
  tcase_add_test(s21_sub_matrix_case, s21_sub_matrix_1);
  tcase_add_test(s21_sub_matrix_case, s21_sub_matrix_2);
  tcase_add_test(s21_mult_number_matrix_case, s21_mult_number_matrix_1);
  tcase_add_test(s21_mult_matrix_case, s21_mult_matrix_1);
  tcase_add_test(s21_mult_matrix_case, s21_mult_matrix_2);
  tcase_add_test(s21_transpose_matrix_case, s21_transpose_matrix_1);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_1);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_2);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_3);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_4);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_5);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_6);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_7);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_8);
  tcase_add_test(s21_determinant_case, s21_determinant_1);
  tcase_add_test(s21_determinant_case, s21_determinant_2);
  tcase_add_test(s21_inverse_matrix_case, s21_inverse_matrix_1);
  tcase_add_test(s21_inverse_matrix_case, s21_inverse_matrix_2);
  tcase_add_test(s21_inverse_matrix_case, s21_inverse_matrix_3);
  // create_matrix
  tcase_add_test(s21_create_matrix_case, test_s21_create_matrix_1);
  tcase_add_test(s21_create_matrix_case, test_s21_create_matrix_2);
  tcase_add_test(s21_create_matrix_case, test_s21_create_matrix_3);
  tcase_add_test(s21_create_matrix_case, test_s21_create_matrix_4);
  // eq_matrix
  tcase_add_test(s21_eq_matrix_case, test_s21_eq_matrix_1);
  tcase_add_test(s21_eq_matrix_case, test_s21_eq_matrix_2);
  tcase_add_test(s21_eq_matrix_case, test_s21_eq_matrix_3);
  tcase_add_test(s21_eq_matrix_case, test_s21_eq_matrix_4);
  tcase_add_test(s21_eq_matrix_case, test_s21_eq_matrix_5);
  tcase_add_test(s21_eq_matrix_case, test_s21_eq_matrix_6);
  // sum_matrix
  tcase_add_test(s21_sum_matrix_case, test_s21_sum_matrix_1);
  tcase_add_test(s21_sum_matrix_case, test_s21_sum_matrix_2);
  // sub_matrix
  tcase_add_test(s21_sub_matrix_case, test_s21_sub_matrix_1);
  tcase_add_test(s21_sub_matrix_case, test_s21_sub_matrix_2);
  // mult_number
  tcase_add_test(s21_mult_number_matrix_case, test_s21_mult_number_1);
  // mult_matrix
  tcase_add_test(s21_mult_matrix_case, test_s21_mult_matrix_1);
  tcase_add_test(s21_mult_matrix_case, test_s21_mult_matrix_2);
  // transpose
  tcase_add_test(s21_transpose_matrix_case, test_s21_transpose_1);
  // calc_complements
  tcase_add_test(s21_calc_complements_case, test_s21_calc_complements_1);
  tcase_add_test(s21_calc_complements_case, test_s21_calc_complements_2);
  tcase_add_test(s21_calc_complements_case, test_s21_calc_complements_3);
  // determinant
  tcase_add_test(s21_determinant_case, test_s21_determinant_1);
  tcase_add_test(s21_determinant_case, test_s21_determinant_2);
  tcase_add_test(s21_determinant_case, test_s21_determinant_4);
  tcase_add_test(s21_determinant_case, test_s21_determinant_5);
  // inverse_matrix
  tcase_add_test(s21_inverse_matrix_case, test_s21_inverse_matrix_1);
  tcase_add_test(s21_inverse_matrix_case, test_s21_inverse_matrix_2);
  tcase_add_test(s21_inverse_matrix_case, test_s21_inverse_matrix_3);
  tcase_add_test(s21_check_matrix_case, test_s21_check_matrix);
  tcase_add_test(s21_check_matrix_case, test_s21_check_matrix_1);

  return x;
}

void suite_test_matrix(void) {
  Suite *x;
  SRunner *y;

  x = test_func_equal();
  y = srunner_create(x);
  srunner_run_all(y, CK_VERBOSE);
  srunner_free(y);
}

int main() { suite_test_matrix(); }