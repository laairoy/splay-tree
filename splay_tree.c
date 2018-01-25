#include "splay_tree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//cria um novo no e caso seja alocado a medoria
// inicializa os valores e devolve o novo no 
S_TREE * criar_no(int chave)
{
   S_TREE *novoNo = (S_TREE *) malloc(sizeof(S_TREE));
   if(!novoNo) return NULL;
   
   novoNo->chave = chave;
   novoNo->dir = novoNo->esq = NULL;
   return novoNo;
}

S_TREE * splay_BU(S_TREE **raiz, int chave)
{
   assert(raiz);
   
   //casos base: raiz nula ou chave está na raiz
   if(!(*raiz))
   {
      return *raiz;
   }
   if((*raiz)->chave == chave) return *raiz;
   
   //busca por elemento chave a esquerda
   if(chave < (*raiz)->chave)
   {
      //chave não está na árvore, retorna-se a raiz
      if((*raiz)->esq == NULL) return *raiz;
      
      //realiza rotação zig-zig direita
      if(chave < (*raiz)->esq->chave)
      {
         splay_BU(&((*raiz)->esq->esq), chave);

         //primeiro rotacionamos uma vez a direita, depois rotacionamos novamente se for o caso
         rotacionar_dir(raiz);
      }
      else

      //rotação zig-zag esquerda/direita   
      if(chave > (*raiz)->esq->chave)
      {
         splay_BU(&((*raiz)->esq->dir), chave);

         //primeiro rotacionamos uma vez a esquerda
         if((*raiz)->esq->dir != NULL) rotacionar_esq(&((*raiz)->esq));
      }
      
      //segunda rotação para direita
      if((*raiz)->esq != NULL) rotacionar_dir(raiz);
      
      return *raiz;
   }
   else
   //busca por elemento chave a direita
   {
      //chave não está na árvore, retorna-se a raiz
      if((*raiz)->dir == NULL) return *raiz;
      
      //rotação zig-zag a esquerda/direita
      if(chave < (*raiz)->dir->chave)
      {
         splay_BU(&((*raiz)->dir->esq), chave);
         
         //primeiro rotacionamos uma vez a direita
         if((*raiz)->dir->esq != NULL) rotacionar_dir(&((*raiz)->dir));
      }
      else

      //rotalçao zig-zig esquerda
      if(chave > ((*raiz)->dir->chave))
      {
         splay_BU(&((*raiz)->dir->dir), chave);
         rotacionar_esq(raiz);
      }
      
      //então, realizamos segunda rotação para esquerda
      if((*raiz)->dir != NULL) rotacionar_esq(raiz);
      
      return *raiz;
   }

}

S_TREE * inserir(S_TREE **raiz, int chave)
{
   //caso base, raiz nula
   if(!(*raiz))
   {
      *raiz = criar_no(chave);
      return *raiz;
   } 
   
   //realiza splay no nó/chave dados
   splay_BU(raiz, chave);

   //verifica se a chave que esta sendo inserida
   //já está na arvore, retorna-se a raiz
   if((*raiz)->chave == chave) return *raiz;
   
   //caso contrário, aloca-se espaço para um novo nó
   S_TREE * novoNo = criar_no(chave);
   
   /* se a chave dada é menor que *raiz->chave
     raiz torna-se filho direito do novo no
     o filho esquerdo da antiga raiz vira filho esquerdo da nova raiz
     filho esquerdo da antiga raiz aponta para NULL */
   if(chave < (*raiz)->chave)
   {
      novoNo->dir = *raiz;
      novoNo->esq = (*raiz)->esq;
      (*raiz)->esq = NULL;
   }

   /* se a chave dada é maior que *raiz->chave
     raiz torna-se filho esquerdo do novo no
     o filho direito da antiga raiz vira filho direito da nova raiz
     filho direito da antiga raiz aponta para NULL */
   else
   {
      novoNo->esq = *raiz;
      novoNo->dir = (*raiz)->dir;
      (*raiz)->dir = NULL;
   }
   
   *raiz = novoNo;
   
   //retorna novoNo como nova raiz da árvore
   return novoNo;
}

S_TREE * buscar_no(S_TREE **raiz, int chave)
{
   //realizamos splay na chave buscada
   splay_BU(raiz, chave);

   //após splay na árvore, se a chave for encontrada
   //ela vira raiz, retornamos a raiz, caso contrário
   //o ultimo nó acessado antes de apontar para NULL
   //torna-se a raiz
   if((*raiz)->chave == chave) return *raiz;

   return NULL;
}

// o procedimento verifica se a raiz e valida
// o auxiliar recebe o raiz
// o filho esquerdo se torna o novo raiz
// o filho esquerdo do auxiliar recebe o filho direito do raiz
// o auxiliar se torna o novo filho direito do raiz
S_TREE * remover_no(S_TREE **raiz, int chave)
{
   S_TREE *aux;

   if(!(*raiz)) return NULL;

   splay_BU(raiz, chave);

   //se a chave não está presente na árvore
   //então, retornamos a raiz
   if((*raiz)->chave != chave)
      return *raiz;

   //se a chave está presente na árvore
   //se o filho esquerdo da raiz é null
   //raiz->dir torna-se raiz
   if(!((*raiz)->esq))
   {
      aux = *raiz;
      *raiz = (*raiz)->dir;
   }

   //se o filho esquedo existe
   else
   {
      aux = *raiz;
      /* desde que (*raiz)->chave == chave
         então realizarmos splay da chave passada
         a árvore não passará a ter filhos direitos na sub-arvore direita
         e o valor maximo na sub-arvore esquerda realizará splay
         ou seja, nova raiz*/
      splay_BU(&((*raiz)->esq), chave);
      *raiz = (*raiz)->esq;
      //faça filho direito da antiga raiz
      //como filho direito da nova raiz
      (*raiz)->dir = aux->dir;
   }

   //free na antiga raiz
   //que é o nó que continha a chave passada
   free(aux);

   //retorna nova raiz que foi feito splay
   return *raiz;
}

void rotacionar_dir(S_TREE **raiz)
{
   assert(raiz);
   
   S_TREE * auxNo = *raiz;
   *raiz = (*raiz)->esq;
   auxNo->esq = (*raiz)->dir;
   (*raiz)->dir = auxNo;
}

void rotacionar_esq(S_TREE **raiz)
{
   assert(raiz);
   
   S_TREE * auxNo = *raiz;
   *raiz = (*raiz)->dir;
   auxNo->dir = (*raiz)->esq;
   (*raiz)->esq = auxNo;
}

void print_emOrdem(S_TREE *raiz)
{
   if(!raiz) return;
   print_emOrdem(raiz->esq);
   printf("%d ", raiz->chave);
   print_emOrdem(raiz->dir);
}