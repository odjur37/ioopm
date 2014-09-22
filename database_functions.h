typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source);

void read_input_file(char *db);

void presets();

void query();

void update();

void insert();

void delete();

void print_database();
