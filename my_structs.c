#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_structs.h"

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;
