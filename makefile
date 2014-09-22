db: db_main.o my_structs.o aux_functions.o print_functions.o
	gcc -g aux_functions.o print_functions.o db_main.o -o db

db_main.o: db_main.c my_structs.o aux_functions.o print_functions.o
	gcc -c -g -std=c99 -Wall db_main.c

aux_functions.o: db_main.o aux_functions.c aux_functions.h
	gcc -c -g -std=c99 -Wall aux_functions.c

print_functions.o: db_main.o print_functions.c print_functions.h
	gcc -c -g -std=c99 -Wall print_functions.c

my_structs.o: my_structs.c my_structs.h
	gcc -c -g -std=c99 -Wall my_structs.c 
