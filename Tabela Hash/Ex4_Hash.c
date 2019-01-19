#include<stdio.h>
#include<stdlib.h>
#define max 20


/*
*Trabalho EXERCICIO 4;
*
@author Luan Felipe S. Silva
*
*/

typedef struct treg *tipopont;

typedef struct tiporegistro{
   int cod,ordem; //cod cliente
   char nome[31]; //nome cliente
   char fone[10]; //tel cliente
} treg;

//Busca Pelo Codigo e Retorna a posição ou (-3) para não encontrado;
int busca (treg *registro, int cod)
{
   int h,g,cont = 0;

   h = cod % max;
   if((registro+h)->cod != cod)
   {
      h = cod % max;
      g = 1 + (cod % (max - 1));
      h = (h+g) % max;

      while((registro+h)->cod != cod)
      {
         if(h >= max-1 && cont < max-1) h = 0;

         else if(cont == max) break;

         h++;
         cont++;
      }
   }
   if((registro+h)->cod == cod) return h;
   else
      return -3;
}

//Tratamento de colisão usando hashing duplo;
int colisao (treg *registro, int cod)
{
   int h,g,cont = 0;

   h = cod % max;
   g = 1 + (cod % (max - 1));
   h = (h+g) % max;

   while((registro+h)->cod != -1)
   {
      if(h >= max-1 && cont < max-1) h = 0;

      else if(cont == max) break;

      h++;
      cont++;
   }
   if((cont<max)&&((registro+h)->cod == -1))
      return h;
   else
      return -2;
}

void main()
{
   int i,op,x;
   treg registro[max], reg;

   for(i=0;i<max;i++)
   {
      registro[i].cod = -1;
   }

   do
   {

      printf("\t\tMenu\n");
      printf("\n\t1 - Incluir Novo Cliente");
      printf("\n\t2 - Alterar Dados Do Cliente");
      printf("\n\t3 - Excluir Cliente");
      printf("\n\t4 - Listar Dados Do Cliente");
      printf("\n\t5 - Listar Todos Clientes");
      printf("\n\t6 - Excluir Todos Registros");
      printf("\n\t7 - Sair");
      printf("\n\tOpcao: ");
      scanf("%d",&op);

      switch(op)
      {
         case 1:{

            system("cls");
            printf("\t1 - Incluir Novo Cliente\n\n");
            printf("Digite o Codigo: ");
            scanf("%d",&reg.cod);

            i = busca(registro, reg.cod);

            if(i == -3)
            {
               printf("Digite o Nome: ");
               scanf("%s", &reg.nome);
               printf("Digite o Telefone: ");
               scanf("%s", &reg.fone);
               reg.ordem++;
               i = reg.cod % max;

               if(registro[i].cod == -1)
               {
                  registro[i] = reg; printf("\nCadastro Realizado!\n\n");
               }
               else
               {
               i = colisao(registro,reg.cod);

               if(i == -2)
                  printf("Sem espaco para mais registros.\n\n");

               else
                  {
                     registro[i] = reg;
                     printf("\nCadastro Realizado!\n\n");
                  }
               }
            }
            else
                  printf("Codigo ja esta em uso.\n\n");
         }break;

         case 2:{

            system("cls");
            printf("\t2 - Alterar Dados Do Cliente\n\n");
            printf("Digite o Codigo do Cliente: ");
            scanf("%d",&reg.cod);
            i = busca(registro, reg.cod);

            if(i != -3)
            {
               printf("Digite Novo Nome: ");
               scanf("%s", &reg.nome);
               printf("Digite Novo Telefone: ");
               scanf("%s", &reg.fone);
               registro[i] = reg;
               printf("\nAlteracao Realizada!\n\n");
            }
            else
               printf("Codigo Nao Encontrado\n\n");
         }break;

         case 3:{

            system("cls");
            printf("\t3 - Excluir Cliente\n\n");
            printf("Digite o Codigo: ");
            scanf("%d",&reg.cod);
            i = busca(registro, reg.cod);

            if(i != -3)
            {
               registro[i].cod = -1;
               printf("Registro Excluido\n\n");
            }
            else
               printf("Codigo Nao Encontrado\n\n");

         }break;

         case 4:{

            system("cls");
            printf("\t4 - Listar Dados Do Cliente\n\n");
            printf("Digite o Codigo: ");
            scanf("%d",&reg.cod);
            i = busca(registro, reg.cod);

            if(i != -3)
            {
               printf("Codigo: %d",registro[i].cod);
               printf("\tNome: %s",registro[i].nome);
               printf("\tTelefone: %s\n\n",registro[i].fone);
            }
            else
               printf("Codigo Nao Encontrado\n\n");
         }break;

         case 5:{

            system("cls");
            printf("\t5 - Listar Todos Clientes\n\n");
            for(i=0;i<max;i++)
            {
               if(registro[i].cod != -1)
               {
                  printf("%dº Inserido",registro[i].ordem);
                  printf("\tCodigo: %d",registro[i].cod);
                  printf("\tNome: %s",registro[i].nome);
                  printf("\tTelefone: %s\n",registro[i].fone);
               }
            }
            printf("\n\n");
         }break;

         case 6:{

            system("cls");
            printf("\t6 - Excluir Todos Registros\n\n");
            printf("1 - Confirmar \t 2 - Voltar\n\n");
            scanf("%d",&x);
            if(x == 1)
            {
               for(i=0;i<max;i++) registro[i].cod = -1;

               printf("\nRegistros Excluidos\n\n");
            }
         }break;
      }
   }while(op != 7);

}
