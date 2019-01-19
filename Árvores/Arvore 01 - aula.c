#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAX  10

typedef int TipoDado;

typedef struct TipoNo *TipoApontador;

typedef struct TipoNo {
  TipoDado Dado;
  TipoApontador Esq, Dir;
} TipoNo;

/* Funçoes */
void Inicializa(TipoApontador *Arvore)
{ *Arvore = NULL; }

void inserir(TipoDado x, TipoApontador *t){
  int ok;
  if (*t == NULL) {                                 // se t aponta para NULL, a inserção é na raiz...
    *t = (TipoApontador)malloc(sizeof(TipoNo));
    if (*t == NULL) return;
    (*t)->Esq = NULL;
    (*t)->Dir = NULL;
    (*t)->Dado = x;
  }
  if (x < (*t)->Dado) {              // Se o dado a ser inserido for menor que o nó atual, recursividade à esquerda
     inserir(x, &(*t)->Esq);
  }
  else{
    if (x > (*t)->Dado) {            // Se o dado a ser inserido for menor que o nó atual, recursividade à direita
       inserir(x, &(*t)->Dir);
    }
  }
}

void exibe_emordem(TipoApontador p){

  if (p == NULL) return ;
  if (p->Esq != NULL)
      exibe_emordem(p->Esq);
  printf("(%d) ", p->Dado);
  if (p->Dir != NULL)
      exibe_emordem(p->Dir);
}

void Central(TipoApontador p)
{ if (p == NULL) return;
  Central(p->Esq);
  printf("%d ", p->Dado);
  Central(p->Dir);
}

void Prefix(TipoApontador p)
{ if (p == NULL) return;
  printf("%d ", p->Dado);
  Prefix(p->Esq);
  Prefix(p->Dir);
}

void Posfix(TipoApontador p)
{ if (p == NULL) return;
  Posfix(p->Esq);
  Posfix(p->Dir);
  printf("%d ", p->Dado);
}

void Busca_Prefix(TipoApontador p, int x)
{ if (p == NULL) return;
  if (p->Dado == x) {printf("%d ", p->Dado); return;}
  Prefix(p->Esq);
  Prefix(p->Dir);
}

TipoApontador busca_elemento(TipoApontador p, int x){

     TipoApontador achou = NULL;

     if (p->Dado == x) return p;
         achou = busca_elemento(p->Esq, x);
     if (p == NULL)
         achou = busca_elemento(p->Dir, x);
     return achou;
}



/* Programa Principal */
int main(int argc, char *argv[])
{
  TipoNo *Arvore;
  int i, j, k, x;

  Inicializa(&Arvore); printf("Inicializou Arvore\n");

  inserir(20, &Arvore); printf("Inseriu: 20\n");
  inserir(50, &Arvore); printf("Inseriu: 50\n");
  inserir(15, &Arvore); printf("Inseriu: 15\n");
  inserir(17, &Arvore); printf("Inseriu: 17\n");
  inserir(10, &Arvore); printf("Inseriu: 10\n");
  inserir(70, &Arvore); printf("Inseriu: 70\n");
  inserir(65, &Arvore); printf("Inseriu: 65\n");

  printf("\nExibe Arvore\n");
  exibe_emordem(Arvore); printf("\n\n");
  printf("\nPrefix..: ");Prefix(Arvore); printf("\n\n");
  printf("\nInfix...: ");Central(Arvore); printf("\n\n");
  printf("\nPosfix..: ");Posfix(Arvore); printf("\n\n");

  return 0;
}
