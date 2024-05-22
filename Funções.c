#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// acha a altura da árvore
int altura(arvore *a) {

  if (a == NULL)
    return 0;
  else {
    int he = altura(a->esq);
    int hd = altura(a->dir);

    if (he > hd) {
      return he + 1;
    } else {
      return hd + 1;
    }
  }
}

// lê a árvore do arquivo
arvore *lerArvore(FILE *arq) {
  char c;
  int num;

  fscanf(arq, "%c", &c);
  fscanf(arq, "%d", &num);

  if (num == -1) {
    fscanf(arq, "%c", &c);
    return NULL;
  } else {
    arvore *a = (arvore *)malloc(sizeof(arvore));
    a->info = num;
    a->esq = lerArvore(arq);
    a->dir = lerArvore(arq);
    fscanf(arq, "%c", &c);
    return a;
  }
}

// Função para ajustar o FB da árvore
void ajustarFB(arvore *a) {
  if (a != NULL) {
    int he = altura(a->esq);
    int hd = altura(a->dir);
    a->FB = hd - he;
    ajustarFB(a->esq);
    ajustarFB(a->dir);
  }
}

// Função para ler a árvore e ajustar o FB dela;
arvore *lerAVL(FILE *arq) {
  arvore *a = lerArvore(arq);
  ajustarFB(a);
  return a;
}

// limpa a árvore da memória
void freearvore(arvore *a) {
  if (a != NULL) {
    freearvore(a->esq);
    freearvore(a->dir);
    free(a);
  }
}

// imprime em pré ordem
void preOrdem(arvore *a) {
  if (a != NULL) {
    printf("%d ", a->info);
    preOrdem(a->esq);
    preOrdem(a->dir);
  }
}

// imprime em ordem
void emOrdem(arvore *a) {
  if (a != NULL) {
    emOrdem(a->esq);
    printf("%d ", a->info);
    emOrdem(a->dir);
  }
}

// imprime em pós ordem
void posOrdem(arvore *a) {
  if (a != NULL) {
    posOrdem(a->esq);
    posOrdem(a->dir);
    printf("%d ", a->info);
  }
}

// imprime nós de um certo nível (usado para imprimir em largura)
void imprimirNosDeUmNivel(arvore *a, int cont, int n) {
  if (a != NULL) {

    if (cont == n) {
      printf("%d ", a->info);
    } else {
      imprimirNosDeUmNivel(a->esq, cont + 1, n);
      imprimirNosDeUmNivel(a->dir, cont + 1, n);
    }
  }
}

// imprime em largura
void largura(arvore *a, int h, int cont) {
  if (a != NULL) {

    imprimirNosDeUmNivel(a, 0, cont);

    if (cont < h) {
      largura(a, h, cont + 1);
    }
  }
}

// verifica se um certo elemendo existe na árvore
int existeABB(arvore *a, int x) {
  if (a != NULL) {
    if (a->info == x)
      return 1;
    else if (x < a->info)
      return existeABB(a->esq, x);
    else if (x > a->info)
      ;
    return existeABB(a->dir, x);
  }
  return 0;
}

// imprime o nível de um certo nó
void nivelDoNoABB(arvore *a, int x, int cont) {
  if (a != NULL) {
    if (a->info == x) {
      printf("%d", cont);
    }

    else if (a->info > x)
      nivelDoNoABB(a->esq, x, cont + 1);
    else if (a->info < x)
      nivelDoNoABB(a->dir, x, cont + 1);
  }
}

// imprime os nós folhas que são menores que um certo valor
void imprimirNosFolhaMenores(arvore *a, int x) {
  if (a != NULL) {
    if (a->info < x) {
      if (a->dir == NULL && a->esq == NULL) {
        printf("%d ", a->info);
      } else {
        imprimirNosFolhaMenores(a->esq, x);
        imprimirNosFolhaMenores(a->dir, x);
      }
    } else {
      imprimirNosFolhaMenores(a->esq, x);
    }
  }
}

// Rotação a esquerda simples
arvore *RotacaoEsqSimples(arvore *r) {
  arvore *a = r;
  arvore *b = a->dir;
  a->dir = b->esq;
  b->esq = a;
  if (b->FB == 1) {
    a->FB = 0;
    b->FB = 0;
  } else {
    a->FB = 1;
    b->FB = -1;
  }
  r = b;
  return r;
}

// Rotação a esquerda dupla
arvore *RotacaoEsqDupla(arvore *r) {
  arvore *a = r;
  arvore *c = a->dir;
  arvore *b = c->esq;
  c->esq = b->dir;
  a->dir = b->esq;
  b->esq = a;
  b->dir = c;

  switch (b->FB) {
  case -1:
    a->FB = 0;
    c->FB = 1;
    break;
  case 0:
    a->FB = 0;
    c->FB = 0;
    break;
  case +1:
    a->FB = -1;
    c->FB = 0;
    break;
  }
  b->FB = 0;
  r = b;
  return r;
}

// Rotação a esquerda geral
arvore *RotacaoEsq(arvore *r) {
  if (r->dir->FB == -1)
    r = RotacaoEsqDupla(r);
  else
    r = RotacaoEsqSimples(r);
  return r;
}

// Rotação para a Direita Simples
arvore *RotacaoDirSimples(arvore *r) {
  arvore *a = r->esq;
  arvore *b = r;
  b->esq = a->dir;
  a->dir = b;
  if (a->FB == -1) {
    a->FB = 0;
    b->FB = 0;
  } else {
    a->FB = 1;
    b->FB = -1;
  }
  r = a;
  return r;
}

// Rotação dupla para a direita
arvore *RotacaoDirDupla(arvore *r) {
  arvore *c = r;
  arvore *a = c->esq;
  arvore *b = a->dir;
  c->esq = b->dir;
  a->dir = b->esq;
  b->esq = a;
  b->dir = c;

  switch (b->FB) {
  case -1:
    a->FB = 0;
    c->FB = 1;
    break;
  case 0:
    a->FB = 0;
    c->FB = 0;
    break;
  case +1:
    a->FB = -1;
    c->FB = 0;
    break;
  }
  b->FB = 0;
  r = b;
  return r;
}

// Rotação para a direita Geral
arvore *RotacaoDir(arvore *r) {
  if (r->esq->FB == 1)
    r = RotacaoDirDupla(r);
  else
    r = RotacaoDirSimples(r);
  return r;
}

// insere um elemendo na árvore
arvore *Inserir(arvore *r, int x, int *hMudou) {
  if (r == NULL) {
    r = malloc(sizeof(arvore));
    r->info = x;
    r->esq = NULL;
    r->dir = NULL;
    r->FB = 0;
    *hMudou = 1;
  } else {
    if (x <= r->info)

    {
      r->esq = Inserir(r->esq, x, hMudou);
      if (*hMudou == 1) {

        switch (r->FB)

        {
        case -1:
          r = RotacaoDir(r);
          *hMudou = 0;
          break;
        case 0:
          r->FB = -1;
          *hMudou = 1;
          break;
        case +1:
          r->FB = 0;
          *hMudou = 0;
          break;
        }
      }
    } else {
      r->dir = Inserir(r->dir, x, hMudou);
      if (*hMudou == 1)

      {
        switch (r->FB) {
        case -1:
          r->FB = 0;
          *hMudou = 0;
          break;
        case 0:
          r->FB = +1;
          *hMudou = 1;
          break;
        case +1:
          r = RotacaoEsq(r);
          *hMudou = 0;
          break;
        }
      }
    }
  }
  return r;
}

// Remove um elemendo na árvore
arvore *Remover(arvore *r, int x, int *hMudou) {
  if (r != NULL) {
    if (r->info == x) {

      if (r->esq == NULL && r->dir == NULL) {
        free(r);
        *hMudou = 1;
        return NULL;
      }

      else if (r->esq == NULL || r->dir == NULL) {
        arvore *aux;
        if (r->esq == NULL) {
          aux = r->dir;
        } else {
          aux = r->esq;
        }
        free(r);
        *hMudou = 1;
        return aux;
      }

      else {
        arvore *maiorEsq = r->esq;
        while (maiorEsq->dir != NULL) {
          maiorEsq = maiorEsq->dir;
        }
        r->info = maiorEsq->info;
        r->esq = Remover(r->esq, r->info, hMudou);

        if (*hMudou == 1) {
          switch (r->FB) {
          case -1:
            r->FB = 0;
            *hMudou = 1;
            break;
          case 0:

            r->FB = 1;
            *hMudou = 0;
            break;
          case +1: {
            int aux = r->dir->FB;
            r = RotacaoEsq(r);
            if (aux == 0)
              *hMudou = 0;
            else
              *hMudou = 1;
            break;
          }
          }
        }
      }
    } else if (x < r->info) {
      r->esq = Remover(r->esq, x, hMudou);
      if (*hMudou == 1) {
        switch (r->FB) {
        case -1:
          r->FB = 0;
          *hMudou = 1;
          break;
        case 0:
          r->FB = 1;
          *hMudou = 0;
          break;
        case +1: {
          int aux = r->dir->FB;
          r = RotacaoEsq(r);
          if (aux == 0)
            *hMudou = 0;
          else
            *hMudou = 1;
          break;
        }
        }
      }

    } else {
      r->dir = Remover(r->dir, x, hMudou);
      if (*hMudou == 1) {
        switch (r->FB) {
        case +1:
          r->FB = 0;
          *hMudou = 1;
          break;
        case 0:
          r->FB = -1;
          *hMudou = 0;
          break;
        case -1: {
          int aux = r->esq->FB;
          r = RotacaoDir(r);
          if (aux == 0) {
            *hMudou = 0;
          } else {
            *hMudou = 1;
          }
          break;
        }
        }
      }
    }
    return r;
  }
}
