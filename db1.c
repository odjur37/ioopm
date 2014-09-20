#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

// Prints welcome text in form of ASCII-art
int print_welcome_text(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
  return -1;
}

// Prints out the database options to the console
void print_options(){
  puts("Please choose an operation");
  puts("1. Query a key");
  puts("2. Update an entry");
  puts("3. New entry");
  puts("4. Remove entry");
  puts("5. Print database");
  puts("0. Exit database");
  printf("? ");
}

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

// tells the user that the file is beaing read
void print_loading_database(char* filename){
  printf("Loading database \"%s\"...\n\n", filename);
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

int request_input(){
  printf("Enter key: ");
  return 1;
}

int inform_of_database_search(){
  puts("Searching database...\n");
  return 1;
}

int inform_of_duplicate_key_search(){
  puts("Searching databse for duplicate keys...");
  return 1;
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

int inform_of_found_entry(){
  puts("Found entry:");
  return 1;
}

int print_key_and_value(opt){
  if (opt != 3){
    printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
  }else{
    printf("key: %s\nvalue: %s\n", list->key, list->value);
  }
  return 1;
}

int print_no_matching_key(char *buffer){
  printf("Could not find an entry matching key \"%s\"!\n", buffer);
  return 1;
}


int inform_of_matching_entry(){
  puts("Matching entry found:");
  return 1;
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

int request_new_value(){
  printf("Enter new value: ");
  return 1;
}

int print_successful_insertion(){
    puts("Value inserted successfully!");
    return 1;
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

int print_key_already_exists(){
  printf("key \"%s\" already exists!\n", cursor->key);
  return 1;
}

int print_key_is_unique(){
  puts("Key is unique!\n");
  return 1;
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

int print_deleted_entry(){
  printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
  return 1;
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
    /*    printf("Could not find an entry matching key \"%s\"!\n", buffer);*/
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
      puts("Good bye!");
      break;
      
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
}
  
int main(int argc, char *argv[]){
  
  // Prints welcome text/ASCII-art
  print_welcome_text(argc, argv);
  
  // Read the input file
  read_input_file(argv[1]);
  
  // Main loop
  main_loop();
  return 0;
} 
