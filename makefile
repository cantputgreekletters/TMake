main:
	gcc src/main.c -Iincl -otmake

debug:
	gcc -g3 -O0 -Wall -Wextra -Wpedantic src/main.c -Iincl -odebug