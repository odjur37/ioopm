#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_functions.h"
#include "print_functions.h"


// creates global int variable choice and sets it to -1
int choice = -1;

int main(int argc, char *argv[]){
  
  // Prints welcome text/ASCII-art
  print_welcome_text(argc, argv);
  
  // Read the input file
  read_input_file(argv[1]);
  
  // Main loop
  while(choice != 0){
    print_options();
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      // Query
      query(choice);
      break;
      
    case 2:
      // Update
      update(choice);
      break;
      
    case 3:
      // Insert
      insert(choice);
      break;
      
    case 4:
      // Delete
      delete(choice);
      break;
      
    case 5:
      // Print database
      print_database();
      break;
      
    case 0:
      // Exit
      print_goodbye();
      break;
      
    default:
      // Please try again
      print_try_again();
    }
    puts("");
  }
  return 0;
} 
