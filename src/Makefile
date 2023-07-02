CC =gcc -g -Wall -Werror -Wextra -std=c11 -D_GNU_SOURSE
OS = $(shell uname -s)
ifeq ($(OS), Linux)
UBU =  -lm -lpthread -lrt -lsubunit
else
UBU = 
endif

all: clean s21_matrix.a gcov_report
s21_matrix.a:
	$(CC) -c s21_create_matrix.c -o s21_create_matrix.o
	$(CC) -c s21_remove_matrix.c -o s21_remove_matrix.o
	$(CC) -c s21_eq_matrix.c -o ss21_eq_matrix.o
	$(CC) -c s21_sum_matrix.c -o s21_sum_matrix.o
	$(CC) -c s21_sub_matrix.c -o s21_sub_matrix.o
	$(CC) -c s21_mult_number.c -o s21_mult_number.o
	$(CC) -c s21_mult_matrix.c -o s21_mult_matrix.o
	$(CC) -c s21_transpose.c -o s21_transpose.o
	$(CC) -c s21_determinant.c -o s21_determinant.o
	$(CC) -c s21_matrix_check.c -o s21_matrix_check.o
	$(CC) -c s21_inverse_matrix.c -o s21_inverse_matrix.o
	$(CC) -c s21_calc_complements.c -o s21_calc_complements.o
	ar rcs s21_matrix.a *.o
		ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) test.c -L. s21_matrix.a -lcheck $(UBU) -o test.out
	./test.out

gcov_report: s21_matrix.a
	$(CC) --coverage *.c -lcheck $(UBU) s21_matrix.a -L. s21_matrix.a -o test.out
	./test.out
	lcov -t "my_test" -c -d ./ --output-file ./test.info
	genhtml -o report test.info
	rm -rf *.gcda *.gch *.gcno *.out *.o *.out
	open report/index.html


style:
	clang-format -i --style=Google *.c
	clang-format -i --style=Google *.h
	clang-format -n --style=Google *.c
	clang-format -n --style=Google *.h

clean:
	rm -rf *.o *.a *.out *.info report test.out.dSYM *.gcno
