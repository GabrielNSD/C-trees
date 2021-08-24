#include <stdio.h>
#include <stdlib.h>

struct noBst
{
    int val;
    struct noBst *esq;
    struct noBst *dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL. 
 **/

struct noBst *alocarNovoNo(int val)
{
    struct noBst *novoNo = (struct noBst *)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

/**
 * Funcao que recebe a raiz de uma BST, e 
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 **/

void inserir(struct noBst **raiz, int val, int *tamanho)
{
    if ((*raiz) == NULL)
    {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else
    {
        if (val <= (*raiz)->val)
        {
            inserir(&(*raiz)->esq, val, tamanho);
        }
        else
        {
            inserir(&(*raiz)->dir, val, tamanho);
        }
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * verifica se a mesma contém um dado valor.
 **/

bool buscar(struct noBst *raiz, int val)
{
    if (raiz == NULL)
    {
        return false;
    }
    if (raiz->val == val)
    {
        return true;
    }
    else
    {
        if (val <= raiz->val)
        {
            return buscar(raiz->esq, val);
        }
        else
        {
            return buscar(raiz->dir, val);
        }
    }
}

/**
 * Funcao que retorna o maior valor de uma BST.
 **/
int max(struct noBst *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    if (raiz->dir == NULL)
    {
        return raiz->val;
    }
    return max(raiz->dir);
}

/**
 * Funcao que retorna o menor valor de uma BST.
 **/
int min(struct noBst *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    if (raiz->esq == NULL)
    {
        return raiz->val;
    }
    return min(raiz->esq);
}

/**
 * Funcao que retorna a altura de uma BST.
 * A altura de uma BST é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 **/
int altura(struct noBst *raiz)
{
    //IMPLEMENTAR
    if (raiz == NULL)
    {
        return 0;
    }

    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        return 0;
    }

    int altura_esquerda = altura(raiz->esq);
    int altura_direita = altura(raiz->dir);

    if (altura_esquerda < altura_direita)
    {
        //std::cout << altura_esquerda << std::endl;
        return altura_direita + 1;
    }
    else
    {
        //std::cout << altura_direita << std::endl;
        return altura_esquerda + 1;
    }
}

// /**
//  * Funcao que navega em-ordem na BST e
//  * imprime seus elementos.
//  **/
// void emOrdem(struct noBst *raiz)
// {
//     //IMPLEMENTAR
// }

// /**
//  * Funcao que navega pre-ordem na BST e
//  * imprime seus elementos.
//  **/
// void preOrdem(struct noBst *raiz)
// {
//     //IMPLEMENTAR
// }

// /**
//  * Funcao que navega pos-ordem na BST e
//  * imprime seus elementos.
//  **/
// void posOrdem(struct noBst *raiz)
// {
//     //IMPLEMENTAR
// }

// /**
//  * Funcao que recebe a raiz de uma BST, e
//  * remove o no que contem o valor passado como
//  * argumento. Tamanho deve ser decrementado.
//  * Tamanho é passado por referência.
//  **/

// struct noBst *remover(struct noBst *raiz, int val, int *tamanho)
// {
//     //IMPLEMENTAR
// }
