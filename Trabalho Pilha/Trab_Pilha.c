/*
Luan Felipe Dos Santos da Silva
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 1000

typedef int TipoApontador;
typedef char TipoChave;

typedef struct
{
    TipoChave Chave;
} TipoItem;

typedef struct
{
    TipoItem Item[MAXTAM];
    TipoApontador Topo;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{
    Pilha -> Topo = 0;
}

int Vazia(TipoPilha Pilha)
{
    return (Pilha.Topo == 0);
}

void Empilha(TipoItem x, TipoPilha *Pilha)
{
    if (Pilha -> Topo == MAXTAM)
        printf(" Erro   pilha esta  cheia\n");
    else
    {
        Pilha->Topo++;
        Pilha->Item[Pilha->Topo - 1] = x;
        printf("\nEmpilhou: %c",x);
    }
}

void Desempilha(TipoPilha *Pilha, TipoItem *Item)
{
    if (Vazia(*Pilha))
        printf(" Erro   pilha esta  vazia\n");
    else
    {
        *Item = Pilha->Item[Pilha->Topo - 1];
        Pilha->Topo--;
        printf("\nDesempilhou: %c", *Item);
    }
}

int Tamanho(TipoPilha Pilha)
{
    return (Pilha.Topo);

}

int continuar()
{
    char x;

    printf("\n\nDeseja continuar (S/N): ");
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

void ExibePilha (TipoPilha * pilha)
{
    int i;

    for(i=0; i < pilha->Topo+1; i++)
        {
            printf("%c",pilha->Item[i]);
        }
}

main()
{
    TipoPilha pilha, posf;
    TipoItem item,x;
    char exp[30];
    char expDigitada[30];
    int i,tam;

    do
    {
        FPVazia(&pilha);
        FPVazia(&posf);

        printf("Digite a expressao: ");
        scanf("%s", &exp);

        for(i=0; exp[i] != '\0'; i++)
        {
            if (exp[i] == '(')
            {
                item.Chave = exp[i];
                Empilha(item, &pilha);
            }

            else if (exp[i]== ')')
            {
                item.Chave = exp[i];

                do
                {
                    if(pilha.Item[pilha.Topo-1].Chave == '(')
                    {
                        Desempilha(&pilha, &item);
                        break;
                    }
                    //Empilha(item, &posf);
                    Desempilha(&pilha, &item);
                    Empilha(item, &posf);


                }
                while(pilha.Item[pilha.Topo+1].Chave != '(' || (pilha.Topo-1 == 0));
            }

            else if (exp[i] == '+' || exp[i] == '-')
            {
                item.Chave = exp[i];
                x.Chave = exp[i];
                while((pilha.Item[pilha.Topo-1].Chave != '(' && pilha.Topo > 0))
                {
                    Desempilha(&pilha, &x);
                    Empilha(x, &posf);
                }
                Empilha(item, &pilha);
            }

            else if (exp[i] == '*' || exp[i] == '/')
            {
                item.Chave = exp[i];
                x.Chave = exp[i];

                while((pilha.Item[pilha.Topo-1].Chave) != '(' && (pilha.Item[pilha.Topo-1].Chave != '+') && (pilha.Item[pilha.Topo-1].Chave != '-') && pilha.Topo > 0)
                {
                    Desempilha(&pilha, &x);
                    Empilha(x, &posf);
                }
                Empilha(item, &pilha);

            }

            else
            {
                item.Chave = exp[i];
                Empilha(item, &posf);
            }

        }

        while(!Vazia(pilha)) {
            Desempilha(&pilha, &x);
            Empilha(x, &posf);
        }


        printf("\n\nExpressao PosFixada: ");
        ExibePilha(&posf);


    }while(continuar());


}

