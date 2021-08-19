#include <stdio.h>
#include <stdlib.h>

struct noBst
{
    int val;
    struct noBst *esq;
    struct noBst *dir;
};

struct noBst *raiz = NULL;

struct noBst *alocarNovoNo(int val)
{
    struct noBst *novoNo = (struct noBst *)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

void inserir(struct noBst **raiz, int val)
{
    if ((*raiz) == NULL)
    {
        (*raiz) = alocarNovoNo(val);
    }
    else
    {
        if (val <= (*raiz)->val)
        {
            inserir(&(*raiz)->esq, val);
        }
        else
        {
            inserir(&(*raiz)->dir, val);
        }
    }
}

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
            buscar(raiz->esq, val);
        }
        else
        {
            buscar(raiz->dir, val);
        }
    }
}