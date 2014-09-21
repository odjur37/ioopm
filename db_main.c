#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "my_structs.h"
#include "print_functions.h"
#include "aux_functions.h"

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

int choice = -1;

int found;

Node cursor; 

char buffer[128]; 

Node list = NULL;

int main(int argc, char *argv[]){
  
  // Prints welcome text/ASCII-art
  print_welcome_text(argc, argv);
  
  // Read the input file
  read_input_file(argv[1]);
  
  // Main loop
  main_loop();
  return 0;
} 
