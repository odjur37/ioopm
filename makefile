db: aux_functions.o global_variables.o main.o
	gcc -g aux_functions.o global_variables.o main.o -o db

aux_functions.o: global_variables.c
	gcc -c -g -std=c99 -Wall aux_functions.c

global_variables.o:
	gcc -c -g -std=c99 -Wall global_variables.c


