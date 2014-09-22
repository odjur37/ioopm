#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aux_functions.h"
#include "print_functions.h"

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

// tells the user that the file is beaing read
void print_loading_database(char* filename){
  printf("Loading database \"%s\"...\n\n", filename);
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

int inform_of_found_entry(){
  puts("Found entry:");
  return 1;
}

int print_key_and_value(char *key, char *value){
  printf("key: %s\nvalue: %s\n", key, value);
  return 1;
}

int print_key_and_value_for_option_3(char *key, char *value){
  printf("key: %s\nvalue: %s\n", key, value);
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

int request_new_value(){
  printf("Enter new value: ");
  return 1;
}

int print_successful_insertion(){
    puts("Value inserted successfully!");
    return 1;
}

int print_key_already_exists(char *key){
  printf("key \"%s\" already exists!\n", key);
  return 1;
}

int print_key_is_unique(){
  puts("Key is unique!\n");
  return 1;
}

int print_deleted_entry(char *key, char *value){
  printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", key, value);
  return 1;
}

int print_goodbye(){
  puts("Good bye!");
  return 1;
}

int print_try_again(){
  puts("Could not parse choice! Please try again");
  return 1;
}
