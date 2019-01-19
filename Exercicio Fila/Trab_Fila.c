/*
Luan Felipe Dos Santos Da Silva
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Celula TipoCelula;

struct Celula
{
    int item;
    TipoCelula *Prox;

};

typedef struct TipoFila
{
    TipoCelula *Frente, *Tras;

} TipoFila;

void CriaFila(TipoFila *Fila)
{
    Fila->Frente = (TipoCelula *) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
}

void Insercao (int item, TipoFila *Fila)
{
    Fila->Tras->Prox = (TipoCelula *) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->item = item;
    Fila->Tras->Prox = NULL;

}

int Retira (TipoFila *Fila)
{
    TipoCelula *aux;

    if (Vazia(*Fila))
    {
        printf("\nErro! Lista de processo esta vazia.\n\n");
        return;
    }

    aux = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;

    int r = Fila->Frente->item;
    free(aux);
    return r;
}

int Vazia(TipoFila Fila)
{
    return (Fila.Frente == Fila.Tras);
}

void Imprime(TipoFila *Fila)
{
    TipoCelula *Aux;
    Aux = Fila->Frente->Prox;
    while (Aux != NULL)
    {
        printf("%d\n", Aux->item);
        Aux = Aux->Prox;
    }
}

int continuar()
{
    char x;

    printf("\n\nDeseja continuar? (S/N): ");
    scanf(" %c",&x);

    do
    {
        if((x!='S')&&(x!='s')&&(x!='N')&&(x!='n'))
        {
            printf("\nOpcao invalida, digite novamente: ");
            scanf(" %c",&x);
        }
    }
    while((x!='S')&&(x!='s')&&(x!='N')&&(x!='n'));

    if(x=='S'|| x=='s')
        return 1;

    else
        return 0;
}


int main()
{
    TipoFila Fila;
    int item;
    int op;

    CriaFila(&Fila);

    do
    {
        system("cls");
        printf("\n\tMENU\n");
        printf("1- Incluir processos\n");
        printf("2- Retirar processo com maior tempo de espera\n");
        printf("3- Exibir processos\n");
        printf("4- Sair\n\n");
        printf ("Escolha a opcao desejada: ");
        scanf ("%d", &op);

        switch(op)
        {
        case 1:
        {
            do
            {
                printf ("Digite o processo: ");
                scanf ("%d", &item);
                Insercao(item, &Fila);
                printf("Enfileirou: %d \n", Fila.Tras->item);
            }while(continuar());
        }
        break;

        case 2:
        {
            printf("Processo com maior tempo de espera: %d",Retira(&Fila));
            getch();

        }
        break;

        case 3:
        {
            system("cls");
            printf("\t3 - Exibir Processos\n ");
            printf("\nLista de processos\n\n");
            Imprime(&Fila);
            getch();
        }
        break;

        case 4: break;

        default:
            printf("Opcao invalida!!!");
            getch();
            break;

        }

    }while(op != 4);

    return 0;
}
