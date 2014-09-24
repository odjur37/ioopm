CC = gcc
FLAGS = -c -ggdb -std=c99 -Wall

db: db_main.o
	gcc -g database_functions.o print_functions.o db_main.o -o db

db_main.o: db_main.c database_functions.o print_functions.o
	$(CC) $(FLAGS) db_main.c

database_functions.o: database_functions.c database_functions.h
	$(CC) $(FLAGS) database_functions.c

print_functions.o: print_functions.c print_functions.h
	$(CC) $(FLAGS) print_functions.c	

clean:
	rm *.o
