GFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

all:
	gcc $(GFLAGS) *.c *.h -o s21_cat
s21_cat:
	gcc $(GFLAGS) *.c *.h -o s21_cat
clean:
	rm -fr *.o *.out  s21_cat

clang:
	clang-format -Werror -n -style=Google *.c
	# cp ../../materials/linters/.clang-format ../grep/
	# clang-format -i *.c *.h

leaks:
	leaks -atExit -- ./s21_cat j y.txt

test:
		bash tests.sh

rebuild: clean s21_cat