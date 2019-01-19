#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//Trabalho Lista ED_I

typedef struct {
    int cod;
    char* nome;
    int qtd;
    float preco;
} Produto;

typedef struct cel {
    Produto produto;
    struct cel* prox;
} Celula;

typedef struct {
    Celula* ini;
    Celula* ult;
    int tam;
} Lista;

void inicializa( Lista* l)
{
    l->ini = malloc(sizeof(Celula));
    l->ult = l->ini;
    l->ult->prox = NULL;
    l->tam = 0;
}

void inserirUltimo(Lista* l, Produto p)
{
    l->ult->prox = malloc(sizeof(Celula));
    l->ult = l->ult->prox;
    l->ult->prox = NULL;
    l->ult->produto = p;
    l->tam++;
}

Produto inserirProduto( int cod, char* nome, int qtd, float preco)
{
    Produto p;
    p.cod =cod;
    p.nome = nome;
    p.qtd = qtd;
    p.preco = preco;
    return p;
}

void imprimirProduto(Produto p)
{
    printf("\nCodigo:%d\t Nome:%s\t Quantidade:%d\t Preco:%.2f", p.cod, p.nome, p.qtd, p.preco);
}

void exibirLista( Lista lista)
{
    Celula* c = lista.ini->prox;
    while ( c != NULL)
    {
        imprimirProduto(c->produto);
        c = c->prox;
    }
}

Celula* buscarProduto(Lista* lista, int cod) {
    Celula* c = lista->ini->prox;
    while ( c != NULL) {
        if(c->produto.cod == cod)
        {
            return c;
        }
        c = c->prox;
    }
    return NULL;
}

void limpaTela()
{
    getch();
    system("cls");
}

int main() {

    Lista estoque;
    inicializa(&estoque);

    int op,op1;
    char* nome;
    int qtd,cod=0,cod2=0;
    float preco;


    do
    {
        printf("\n\tMenu Principal\n\n");
        printf("1 - Compra de produtos\n");
        printf("2 - Venda de produtos\n");
        printf("3 - Listar quantidade de produto em estoque\n");
        printf("4 - Consultar produto\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&op);
        switch (op)
        {
            case 1:
            {
                system("cls");
                printf("\t\t1 - Compra de produtos\n");
                printf("1 - Inserir novo produto.\n2 - Inserir produto ja existente.\n");
                printf("Opcao: ");
                scanf("%d",&op1);
                if(op1==1)
                {
                    cod++;
                    nome = (char*) malloc(sizeof(char)*20);
                    printf("\nDigite  o nome do produto: ");
                    scanf("%s",nome);
                    printf("Digite a quantidade de produtos: ");
                    scanf("%d", &qtd);
                    printf("Digite o preco do produto: ");
                    scanf("%f", &preco);
                    inserirUltimo(&estoque, inserirProduto(cod, nome, qtd, preco));
                    printf("\nCompra realizada com sucesso!");
                    limpaTela();
                }
                else
                {
                     printf("Digite o codigo do produto: ");
                     scanf("%d",&cod);
                     Celula* c = buscarProduto(&estoque, cod);

                    if ( c != NULL )
                    {
                        printf("\nProduto encontrado:");
                        imprimirProduto(c->produto);
                        int qtd;
                        printf("\n\nDigite a quantidade de produtos a ser inserido: ");
                        scanf("%d", &qtd);
                        c->produto.qtd += qtd;
                        printf("\nCompra realizada com sucesso!");
                        limpaTela();
                    }
                    else
                    {
                        printf("\nProduto nao encontrado!");
                        limpaTela();
                    }
                }

            }break;

            case 2:
            {
                system("cls");
                printf("\t2 - Venda de produtos\n");
                printf("\nDigite o codigo do produto: ");
                scanf("%d",&cod2);
                Celula* c = buscarProduto(&estoque, cod2);

                if ( c != NULL )
                {
                    printf("\nProduto encontrado:");
                    imprimirProduto(c->produto);
                    int qtd;
                    printf("\n\nDigite a quantidade de produtos vendidos: ");
                    scanf("%d", &qtd);

                    if(qtd<c->produto.qtd)
                    {
                        c->produto.qtd -= qtd;
                        printf("Venda realizada com sucesso!");
                        limpaTela();
                        break;
                    }

                    else
                    {
                        printf("\nQuantidade de produtos %c maior que quantidade em estoque.",130);
                        limpaTela();
                        break;
                    }
                 }
                 else
                    printf("\nProduto nao encontrado!");
                    limpaTela();

            }break;

            case 3:
            {
                system("cls");
                printf("3 - Lista dos produtos\n");
                exibirLista(estoque);
                limpaTela();
            }break;

            case 4:
            {
                system("cls");
                printf("4 - Consultar produto\n");
                printf("Digite o codigo do produto: ");
                scanf("%d",&cod);
                Celula* c = buscarProduto(&estoque, cod);

                if ( c != NULL )
                {
                    printf("\nProduto encontrado:");
                    imprimirProduto(c->produto);
                }
                else
                    printf("\nProduto nao encontrado!");
                    limpaTela();

            }break;

            case 5:
                printf("\n\nSair!!!\n\n");
                break;

            default:
            {
                printf("\n\nOpcao invalida!");
                limpaTela();
            }break;
        }

    }while(op!=5);

    return 0;
}
