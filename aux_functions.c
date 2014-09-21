#include "aux_functions.h"
#ifndef "my_structs.h"
#define "my_structs.h"

// creates global int variable choice and sets it to -1
int choice = -1;

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
  while(!(feof(database))){
    Node newNode = malloc(sizeof(struct node));
    readline(buffer, 128, database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    readline(buffer, 128, database);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
  }
}

void presets(){
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
void query(){
  presets();
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      inform_of_found_entry();
      print_key_and_value(1);
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
void update(){
  presets();
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      inform_of_matching_entry();
      print_key_and_value(2);
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
void insert(){
  presets();
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      print_key_already_exists();
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
    print_key_and_value(3);
  }
}

// Option 4
void delete(){
  presets();
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
	list = cursor->next;
      }else{
	prev->next = cursor->next;
      }
      found = 1;
      print_deleted_entry();
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

void main_loop(){
  while(choice != 0){
    print_options();
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      // Query
      query();
      break;
      
    case 2:
      // Update
      update();
      break;
      
    case 3:
      // Insert
      insert();
      break;
      
    case 4:
      // Delete
      delete();
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
}

#endif
