#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_functions.h"
#include "print_functions.h"

// creates global int variable found
int found;

// creates global Node variable cursor
Node cursor; 

// creates a 128 bytes long array in the variable buffer
char buffer[128]; 

// sets the Node-variable list as a pointer to NULL
Node list = NULL;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

// Reads the database-file
void read_input_file(char *db){
  char *filename = db;
  print_loading_database(db);
  FILE *database = fopen(filename, "r");
  while(!(feof(database))){                      //Sålänge !EOF db, loopa:
    Node newNode = malloc(sizeof(struct node));  //Reserverar plats i stacken för en node
    readline(buffer, 128, database);             //Läs första entryt i db och ersätt radbrytning med null-tecknet
    newNode->key = malloc(strlen(buffer) + 1);   //Allokera minne för längden för nodens key
    strcpy(newNode->key, buffer);                //Kopiera "key" till arrayen "buffer"
    readline(buffer, 128, database);             //Läs 
    newNode->value = malloc(strlen(buffer) + 1); //
    strcpy(newNode->value, buffer);              //kopiera value-strängen till arrayen buffer
    newNode->next = list;                        //
    list = newNode;                              //skapar newNode på nextplatsen för att skapa en plats för nästa entry i db
  }
}

void presets(int choice){
  request_input();
  readline(buffer, 128, stdin);
  if (choice != 3){
    inform_of_database_search();
  }
  else{
    inform_of_duplicate_key_search();
  }
  found = 0;
  cursor = list;
}

// Option 1
void query(int choice){
  presets(choice);
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      inform_of_found_entry();
      print_key_and_value(cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    print_no_matching_key(buffer);
  }
}

// Option 2
void update(int choice){
  presets(choice);
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      inform_of_matching_entry();
      print_key_and_value(cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    print_no_matching_key(buffer);
  }else{
    request_new_value();
    readline(buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    print_successful_insertion();
  }
}

// Option 3
void insert(int choice){
  presets(choice);
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      print_key_already_exists(cursor->key);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){ // Insert new node to the front of the list
    print_key_is_unique();
    Node newNode = malloc(sizeof(struct node));
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    request_new_value();                      // Requests new value from user
    readline(buffer, 128, stdin);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
    puts("");
    print_successful_insertion();
    print_key_and_value_for_option_3(list->key, list->value);
  }
}

// Option 4
void delete(int choice){
  presets(choice);
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
	list = cursor->next;
      }else{
	prev->next = cursor->next;
      }
      found = 1;
      print_deleted_entry(cursor->key, cursor->value);
    }else{
      prev = cursor;
      cursor = cursor->next;
    }
  }
  if(!found){
    print_no_matching_key(buffer);
  }
}

// Option 5
void print_database(){
  cursor = list;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}
