#include<stdio.h>
#include<stdlib.h>

/* Trabalho Árvore Binária
*
*@author LUAN FELIPE DOS SANTOS DA SILVA
*LED-II
*/


typedef struct TipoData
{
   int dia, mes, ano;

}TipoData;

typedef struct TipoRegistro
{
    int matricula,cargo;
    char nome[21];
    float salario;
    TipoData data;

} TipoRegistro;

typedef struct TipoNo * TipoApontador;
typedef struct TipoNo {
  TipoRegistro Reg;
  TipoApontador Esq, Dir;
} TipoNo;
typedef TipoApontador TipoDicionario;

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

void Inicializa(TipoApontador *Dicionario)
{
    *Dicionario = NULL;
}

void ExibeFuncionario(TipoApontador *p)
{
    printf("\n#------------------------#\n");
    printf("\nMatricula: %d\n",(*p)->Reg.matricula);
    printf("Nome: %s  \n",(*p)->Reg.nome);
    printf("Cargo: %d\n",(*p)->Reg.cargo);
    printf("Admissao: %d/ %d/ %d \n",(*p)->Reg.data);
    printf("Salario: %.2f\n",(*p)->Reg.salario);
}

void Insere(TipoRegistro x, TipoApontador *p)
{
    if (*p == NULL)
    {
        *p = (TipoApontador)malloc(sizeof(TipoNo));
        (*p)->Reg = x;
        (*p)->Esq = NULL;
        (*p)->Dir = NULL;
        return;
    }
    if (x.matricula < (*p)->Reg.matricula)
    {
        Insere(x, &(*p)->Esq);
        return;
    }
    if (x.matricula > (*p)->Reg.matricula)
        {Insere(x, &(*p)->Dir);
        }
    else
        printf("Erro : Registro ja existe na arvore\n");
}

void Posfix(TipoApontador p)
{ if (p == NULL) return;
  Posfix(p->Esq);
  Posfix(p->Dir);
  printf("%ld  ", p->Reg.matricula);
}

/*Verifica se a matricula já foi inserida
antes de inserir os outros dados*/
int VerificaMatricula(TipoRegistro *x, TipoApontador *p)
{
    if (*p == NULL)
    {
        return 0;
    }
    if (x->matricula < (*p)->Reg.matricula)
    {
        VerificaMatricula(x, &(*p)->Esq);
        return;
    }
    if (x->matricula > (*p)->Reg.matricula)
        VerificaMatricula(x, &(*p)->Dir);
    else
    {
        *x = (*p)->Reg;
        return 1;
    }
}

void Pesquisa(TipoRegistro *x, TipoApontador *p)
{
    if (*p == NULL)
    {
        printf("\nErro: Registro nao esta presente na arvore\n\n");
        system("pause");
        return;
    }
    if (x->matricula < (*p)->Reg.matricula)
    {
        Pesquisa(x, &(*p)->Esq);
        return;
    }
    if (x->matricula > (*p)->Reg.matricula)
        Pesquisa(x, &(*p)->Dir);
    else
    {
        *x = (*p)->Reg;
        printf("\nMatricula Encontrada\n\n");
        ExibeFuncionario(&(*p));
        system("pause");
    }
}

void Antecessor(TipoApontador q, TipoApontador *r)
{
    if ((*r)->Dir != NULL)
    {
        Antecessor(q, &(*r)->Dir);
        return;
    }
    q->Reg = (*r)->Reg;
    q = *r;
    *r = (*r)->Esq;
    free(q);
}

void Retira(TipoRegistro x, TipoApontador *p)
{
    TipoApontador Aux;

    if (*p == NULL)
    {
        printf("\nErro : Registro nao esta na arvore\n");
        return;
    }
    if (x.matricula < (*p)->Reg.matricula)
    {
        Retira(x, &(*p)->Esq);
        return;
    }
    if (x.matricula > (*p)->Reg.matricula)
    {
        Retira(x, &(*p)->Dir);
        return;
    }
    if ((*p)->Dir == NULL)
    {
        Aux = *p;
        *p = (*p)->Esq;
        free(Aux);
        return;
    }
    if ((*p)->Esq != NULL)
    {
        Antecessor(*p, &(*p)->Esq);
        return;
    }
    Aux = *p;
    *p = (*p)->Dir;
    free(Aux);
}

/*Pesquisa por funcionarios que estao no mesmo cargo*/
void BuscaCargo(TipoRegistro x, TipoApontador *p)
{

    if ((*p) == NULL) return;

    if(x.cargo == (*p)->Reg.cargo)
    {
        ExibeFuncionario(&(*p));
    }
        BuscaCargo(x, &(*p)->Dir);
        BuscaCargo(x, &(*p)->Esq);
}

/*Faz a pesquisa na arvore pelos salarios que estao dentro da faixa*/
void BuscaSalario(float si,float sf, TipoApontador *p)
{
    if ((*p) == NULL) return;

    if(si <= (*p)->Reg.salario && sf >= (*p)->Reg.salario)
    {
        ExibeFuncionario(&(*p));
    }
    BuscaSalario(si, sf, &(*p)->Dir);
    BuscaSalario(si, sf, &(*p)->Esq);
}

/*Verifica se a data inserida é valida e
aceita funcionarios contratados até o ano de 2015*/
TipoData VerificaData()
{
    TipoData data;

    printf("\nData de Admissao");
    printf("\n\tDia: ");
    scanf("%d",&data.dia);
    printf("\tMes: ");
    scanf("%d",&data.mes);
    printf("\tAno: ");
    scanf("%d",&data.ano);

    if((data.dia>31||data.dia<1)||(data.mes>12||data.mes<1)||(data.ano<1900||data.ano>2015))
    {
        printf("\nData inserida invalida\n");
        getch();
        system("cls");
        VerificaData();
    }
    else
        return data;
}

/*Faz a verificação se o cargo inserido é valido*/
int VerificaCargo()
{
    int aux;
    do
    {
        printf("\n\n\tCargo do Funcionario");
        printf("\n1 - Diretor");
        printf("\n2 - Gerente");
        printf("\n3 - Vendedor");
        printf("\n4 - Analista de Credito");
        printf("\n5 - Vigilante");
        printf("\n\nInsira o cargo: ");
        scanf("%d",&aux);

        if(aux>=1 && aux<=5) return aux;
        else
        {
            printf("\nOpcao Digitada Invalida!!!\n");
            getch();
            system("cls");
        }
    }while(aux<1||aux>5);
}

/*INICIO DA FUNÇÃO PRINCIPAL*/
int main(int argc, char *argv[])
{
    int op;
    TipoNo *Dicionario;
    TipoRegistro x;
    float inicial,fim;

    Inicializa(&Dicionario);

    do
    {
        system("cls");
        printf("\t\t Menu Principal \n");
        printf("\n\t1 - Inserir\n");
        printf("\t2 - Remover\n");
        printf("\t3 - Pesquisar\n");
        printf("\t4 - Exibir Todos\n");
        printf("\t5 - Exibir Cargos\n");
        printf("\t6 - Faixa Salarial\n");
        printf("\t7 - Sair\n");
        printf("\n\tOpcao: ");
        scanf("%d",&op);

        switch(op)
        {
            case 1:
            {
                do
                {
                    system("cls");
                    printf("\t\t1 - Inserir Funcionario\n\n");
                    printf("Numero da Matricula: ");
                    scanf("%d",&x.matricula);
                    if(VerificaMatricula(&x,&Dicionario) == 0)
                    {
                        printf("Nome do Funcionario: ");
                        scanf("%s", x.nome);
                        printf("Salario: ");
                        scanf("%f",&x.salario);
                        x.data = VerificaData();
                        x.cargo = VerificaCargo();
                        Insere(x,&Dicionario);
                    }
                    else
                        {printf("\nInsira outra matricula.");
                        printf(" Numero de matricula ja esta em uso.\n");}

                }while(continuar()==1);

            }break;

            case 2:
            {
                do{
                system("cls");
                printf("\t\t2 - Remover\n\n");
                printf("Digite a matricula do funcionario a ser removido: ");
                scanf("%d",&x.matricula);
                Retira(x,&Dicionario);
                }while(continuar() == 1);

                /*Função Procura Percorre a arvore em busca do nó a ser removido
                se o nó tiver filhos ela procura primeiramente o filho da esquerda
                se for igual a NULL ela procura o da direita e passa como
                parametro para a Função Antecessor que copia o conteudo do filho para o pai
                fazendo os outros nós irmaos se tornarem filhos.*/

            }break;

            case 3:
            {
                printf("\t\t3 - Pesquisar\n\n");
                printf("Digite a matricula que deseja pesquisar: ");
                scanf("%d",&x.matricula);
                Pesquisa(&x, &Dicionario);

            }break;

            case 4:
            {
                printf("\nCaminhamento Pos-Fixado...: ");
                Posfix(Dicionario);
                getch();
                system("cls");

            }break;

            case 5:
            {
                system("cls");
                printf("\t\t5 - Exibir Cargo");
                x.cargo = VerificaCargo();
                BuscaCargo(x,&Dicionario);
                getch();
            }break;

            case 6:
            {
                system("cls");
                printf("\t\t6 - Funcionarios por faixa de salarial\n\n");
                printf("Salario Inicial: ");
                scanf("%f",&inicial);
                printf("\nSalario Final: ");
                scanf("%f",&fim);
                BuscaSalario(inicial, fim, &Dicionario);
                getch();

            }break;

            case 7:
            {
                system("cls");
                printf("\n7 - SAIR\n\n");
            }break;

            default:
            {
                printf("Opcao digitada incorreta!!");
            }
        }
    }while(op!=7);
}
