#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_structs.h"
#include "aux_functions.h"
#include "print_functions.h"

int main(int argc, char *argv[]){
  
  // Prints welcome text/ASCII-art
  print_welcome_text(argc, argv);
  
  // Read the input file
  read_input_file(argv[1]);
  
  // Main loop
  main_loop();
  return 0;
} 
