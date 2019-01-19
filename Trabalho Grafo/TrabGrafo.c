/*
*
*Luan Felipe Dos Santos
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1
#define INFINITO        INT_MAX
#define MB              1024 /* Referente a velocidade de transferencia de arquivos*/
#define PRECO           1.50/*Preço por metro de cabo*/

typedef int TipoValorVertice;
typedef int TipoPeso;
typedef struct TipoGrafo {
  TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
  int  NumVertices;
  int  NumArestas;
} TipoGrafo;

typedef int  TipoApontador;

typedef int  TipoIndice;

typedef struct TipoItem {
  TipoPeso Chave;
} TipoItem;

typedef TipoItem Vetor[MAXNUMVERTICES + 1];


TipoApontador Aux;
int  i, NArestas;
short  FimListaAdj;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo;
TipoValorVertice NVertices;
TipoIndice n;   /*Tamanho do heap*/
TipoValorVertice Raiz;

void FGVazio(TipoGrafo *Grafo)
{ int  i, j;
  for (i = 0; i <= Grafo->NumVertices; i++)
    { for (j = 0; j <= Grafo->NumVertices; j++)
         Grafo->Mat[i][j] = 0;
    }
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGrafo *Grafo)
{
   Grafo->Mat[*V1][*V2] = *Peso;
}

short  ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo)
{
   return (Grafo->Mat[Vertice1][Vertice2] > 0);
}


/*-- Operadores para obter a lista de adjacentes --*/
short  ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoApontador Aux = 0;
  short ListaVazia = TRUE;
  while (Aux < Grafo->NumVertices && ListaVazia)
    { if (Grafo->Mat[*Vertice][Aux] > 0)
      ListaVazia = FALSE;
      else
       Aux++;
    }
  return (ListaVazia == TRUE);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoValorVertice Result;
  TipoApontador Aux = 0;
  short Listavazia = TRUE;
  while (Aux < Grafo->NumVertices && Listavazia)
    { if (Grafo->Mat[*Vertice][Aux] > 0)
      { Result = Aux;
        Listavazia = FALSE;
      }
      else
    Aux++;
  }
  if (Aux == Grafo->NumVertices)
  printf("Erro: Lista adjacencia vazia (PrimeiroListaAdj)\n");
  return Result;
}


void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo,
         TipoValorVertice *Adj, TipoPeso *Peso,
         TipoApontador *Prox, short *FimListaAdj)
{ /* --Retorna Adj apontado por Prox--*/
  *Adj = *Prox;
  *Peso = Grafo->Mat[*Vertice][*Prox];
  (*Prox)++;
  while (*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)
    (*Prox)++;
  if (*Prox == Grafo->NumVertices)
  *FimListaAdj = TRUE;
}

void ImprimeGrafo(TipoGrafo *Grafo)
{
   int i, j;
   printf("\n\t\tMatriz Adjacente\n\n");
  printf("   ");
  for (i = 0; i < Grafo->NumVertices; i++)
    printf(" %3d", i);
  putchar('\n');
  for (i = 0; i < Grafo->NumVertices; i++)
    { printf("%3d", i);
      for (j = 0; j < Grafo->NumVertices; j++)
        printf("%4d", Grafo->Mat[i][j]);
      putchar('\n');
    }
}

/* Local variables for AgmPrim: */
struct LOC_AgmPrim {
  TipoPeso P[MAXNUMVERTICES + 1];
  TipoValorVertice Pos[MAXNUMVERTICES + 1];
} ;

void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A,
              TipoPeso *P, TipoValorVertice *Pos)
{ TipoIndice i = Esq;
  int j = i * 2;
  TipoItem x;
  x = A[i];
  while (j <= Dir)
  { if (j < Dir)
    { if (P[A[j].Chave] > P[A[j+1].Chave]) j++; }
    if (P[x.Chave] <= P[A[j].Chave]) goto L999;
    A[i] = A[j]; Pos[A[j].Chave] = i;
    i = j; j = i * 2;
  }
  L999: A[i] = x;
  Pos[x.Chave] = i;
}

void Constroi(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos)
{ TipoIndice Esq;
  Esq = n / 2 + 1;
  while (Esq > 1) { Esq--; RefazInd(Esq, n, A, P, Pos); }
}

TipoItem RetiraMinInd(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos)
{ TipoItem Result;
  if (n < 1) { printf("Erro: heap vazio\n"); return Result; }
  Result = A[1]; A[1] = A[n];
  Pos[A[n].Chave] = 1; n--;
  RefazInd(1, n, A, P, Pos );
  return Result;
}

void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A,
                     TipoPeso *P, TipoValorVertice *Pos)
{ TipoItem x;
  if (ChaveNova > P[A[i].Chave])
  { printf("Erro: Chave Nova maior que a chave atual\n");
    return;
  }
  P[A[i].Chave] = ChaveNova;
  while (i > 1 && P[A[i / 2].Chave] > P[A[i].Chave])
    { x = A[i / 2]; A[i / 2] = A[i];
      Pos[A[i].Chave] = i / 2; A[i] = x;
      Pos[x.Chave] = i; i /= 2;
    }
}

void AgmPrim(TipoGrafo *Grafo, TipoValorVertice *Raiz, int Arq)
{
    int  Antecessor[MAXNUMVERTICES + 1], dist=0;
    float preco;
    short  Itensheap[MAXNUMVERTICES + 1];
    Vetor A;
    TipoPeso P[MAXNUMVERTICES + 1];
    TipoValorVertice Pos[MAXNUMVERTICES + 1];
    TipoValorVertice u, v;
    TipoItem TEMP;
    for (u = 0; u <= Grafo->NumVertices; u++)
    {
        /*Constroi o heap com todos os valores igual a INFINITO*/
        Antecessor[u] = -1;
        P[u] = INFINITO;
        A[u+1].Chave = u;   /*Heap a ser construido*/
        Itensheap[u] = TRUE;
        Pos[u] = u + 1;
    }
    n = Grafo->NumVertices;
    P[*Raiz] = 0;
    Constroi(A, P, Pos);
    while (n >= 1)  /*enquanto heap nao vazio*/
    {
        TEMP = RetiraMinInd(A, P, Pos);
        u = TEMP.Chave;
        Itensheap[u] = FALSE;
        if (u != *Raiz)
            {
               printf("Menor Caminho: %d -> %d Distancia: %d metros Tempo: %ds  \n", Antecessor[u], u, P[u], (Arq/MB*P[u]));
               dist = P[u]+dist;
            }
        if (!ListaAdjVazia(&u, Grafo))
        {
            Aux = PrimeiroListaAdj(&u, Grafo);
            FimListaAdj = FALSE;
            while (!FimListaAdj)
            {
                ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
                if (Itensheap[v] && Peso < P[v])
                {
                    Antecessor[v] = u;
                    DiminuiChaveInd(Pos[v], Peso, A, P, Pos);
                }
            }
        }
    }
    printf("\n\nCusto total: %.2f reais",(PRECO*dist));
    printf("\tTotal de Cabos: %d Metros",dist);
}

/* ============================================================= */
int main(int argc, char *argv[])
{ /*-- Programa principal --*/
  int TEMP, Arq, op;

  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/

  printf("No. vertices: 6 \n");
  NVertices = 6;
  printf("No. arestas: 15\n");
  NArestas = 15;
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);
  ImprimeGrafo(&Grafo);

    V1 = 0;
    V2 = 1;
    Peso = 4;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 0;
    V2 = 2;
    Peso = 5;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 0;
    V2 = 3;
    Peso = 4;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 0;
    V2 = 4;
    Peso = 7;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 0;
    V2 = 5;
    Peso = 6;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 1;
    V2 = 2;
    Peso = 1;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 1;
    V2 = 3;
    Peso = 8;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 1;
    V2 = 4;
    Peso = 15;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 1;
    V2 = 5;
    Peso = 20;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 2;
    V2 = 3;
    Peso = 14;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 2;
    V2 = 4;
    Peso = 3;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 2;
    V2 = 5;
    Peso = 10;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 3;
    V2 = 4;
    Peso = 11;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 3;
    V2 = 5;
    Peso = 9;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    V1 = 4;
    V2 = 5;
    Peso = 2;
    Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    InsereAresta(&V2, &V1, &Peso, &Grafo);

    do
    {

        ImprimeGrafo(&Grafo);
        printf("\nVertice Raiz: ");
        scanf("%d%*[^\n]", &TEMP);
        printf("\n Tamanho do Arquivo em MB: ");
        scanf("%d%*[^\n]", &Arq);
        getchar();
        Raiz = TEMP;
        AgmPrim(&Grafo, &Raiz, Arq);
        printf("\n\nDeseja sair: 1-Sim  2-Nao \n \tOpcao:");
        scanf("%d", &op);
        system("cls");

    }
    while(op!=1);

  return 0;
}
