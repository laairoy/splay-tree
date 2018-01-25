#include "splay_tree.h"
#include <stdlib.h>
#include <stdio.h>

void my_print(S_TREE *raiz)
{
   printf("chave inserida é: %d\n", raiz->chave);
   if(raiz->esq) printf("Filho esquerdo é: %d\n", raiz->esq->chave);
   else printf("Filho esquerdo é: NULL\n");
   if(raiz->dir) printf("Filho direito é: %d\n\n", raiz->dir->chave);
   else printf("Filho direito é: NULL\n\n");
}
int main()
{
   S_TREE *raiz = NULL;
   inserir(&raiz, 5);
   my_print(raiz);
   
   inserir(&raiz, 6);
   my_print(raiz);
   
   inserir(&raiz, 20);
   my_print(raiz);

   inserir(&raiz, 15);
   my_print(raiz);

   inserir(&raiz, 23);
   buscar_no(&raiz, 6);
   my_print(raiz);
   
   remover_no(&raiz, 6);
   my_print(raiz);

   print_emOrdem(raiz);


   return 0;
}
