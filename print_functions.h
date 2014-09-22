int print_welcome_text(int argc, char *argv[]);

void print_options();

void print_loading_database(char* filename);

int request_input();

int inform_of_database_search();

int inform_of_duplicate_key_search();

int inform_of_found_entry();

int print_key_and_value(char *key, char *value);

int print_key_and_value_for_option_3(char *key, char *value);

int print_no_matching_key(char *buffer);

int inform_of_matching_entry();

int request_new_value();

int print_successful_insertion();

int print_key_already_exists(char *key);

int print_key_is_unique();

int print_deleted_entry(char *key, char *value);

int print_goodbye();

int print_try_again();
