#ifndef SPLAY_TREE
#define SPLAY_TREE

typedef struct no
{
	int chave;
	struct no *dir, *esq;
}S_TREE;

S_TREE * criar_no(int chave);

S_TREE * splay_BU(S_TREE **raiz, int chave);

S_TREE * inserir(S_TREE **raiz, int chave);
//S_TREE * inserir(S_TREE *esq, S_TREE **raiz, S_TREE *dir, int chave);

S_TREE * buscar_no(S_TREE **raiz, int chave);

S_TREE * remover_no(S_TREE **raiz, int chave);

void rotacionar_dir(S_TREE **raiz);

void rotacionar_esq(S_TREE **raiz);

void print_emOrdem(S_TREE *raiz);
#endif
