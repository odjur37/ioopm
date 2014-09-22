CC = gcc
FLAGS = -c -ggdb -std=c99 -Wall

db: db_main.o my_structs.o aux_functions.o print_functions.o
	gcc -g aux_functions.o print_functions.o db_main.o -o db

db_main.o: db_main.c my_structs.o aux_functions.o print_functions.o
	$(CC) $(FLAGS) db_main.c

aux_functions.o: db_main.o aux_functions.c aux_functions.h
	$(CC) $(FLAGS) aux_functions.c

print_functions.o: db_main.o print_functions.c print_functions.h
	$(CC) $(FLAGS) print_functions.c

my_structs.o: my_structs.c my_structs.h
	$(CC) $(FLAGS) my_structs.c 
