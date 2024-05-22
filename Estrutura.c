#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct arvore {
  int FB;
  int info;
  struct arvore *esq;
  struct arvore *dir;
} arvore;
