GFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

all:
	gcc $(GFLAGS) *.c *.h -o s21_grep
s21_grep:
	gcc $(GFLAGS) *.c *.h -o s21_grep
clean:
	rm -fr *.o *.out s21_grep

clang:
	clang-format -Werror -n -style=Google *.c
	# cp ../../materials/linters/.clang-format ../grep/
	# clang-format -i *.c *.h

leaks:
	leaks -atExit -- ./s21_grep j y.txt

test:
		bash tests.sh

rebuild: clean s21_grep