#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBst *no);
struct noBst *balancear(struct noBst *no);
struct noBst *rebalancearEsqEsq(struct noBst *no);
struct noBst *rebalancearEsqDir(struct noBst *no);
struct noBst *rebalancearDirDir(struct noBst *no);
struct noBst *rebalancearDirEsq(struct noBst *no);

/**
 * Embora durante a aula eu disse que precisaríamos
 * das variáveis alturaEsq e alturaDir, na verdade não
 * é necessário. Depois de implementar que percebi algo
 * óbvio: para pegar a altura de uma sub-árvore basta
 * obter o valor da variável altura na sub-árvore. (:
 **/
struct noBst
{
    int val;
    int altura;
    int balanco;
    struct noBst *esq;
    struct noBst *dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL,
 * e vari�veis altura e balanco para 0.
 **/
struct noBst *alocarNovoNo(int val)
{
    //IMPLEMENTAR
    struct noBst *novoNo = (struct noBst *)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->altura = 0;
    novoNo->balanco = 0;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBst *rotacaoDireita(struct noBst *arvore)
{
    //IMPLEMENTAR

    struct noBst *temp = arvore->esq;
    arvore->esq = arvore->esq->dir;
    temp->dir = arvore;
    atualizar(temp);
    return temp;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBst *rotacaoEsquerda(struct noBst *arvore)
{
    //IMPLEMENTAR
    struct noBst *temp = arvore->dir;
    arvore->dir = arvore->dir->esq;
    temp->esq = arvore;
    atualizar(temp);
    return temp;
}

// /**
//  * Funcao que recebe a raiz de uma BST, e
//  * insere um novo valor na BST. Tamanho deve
//  * ser incrementado.
//  * Ambos tamanho e raiz são passados por refer�ncia.
//  * Lembrar de atualizar altura e fator de balanco dos n�s
//  * antecessores do n� inserido, bem como balance�-los caso
//  * seja necess�rio.
//  * Dica: reutilizar a fun��o de inserir de BST, e lembrar
//  * de como usar inteligentemente a recurs�o para conseguir
//  * atualizar e balancear os n�s antecessores.
//  **/
void inserir(struct noBst **raiz, int val, int *tamanho)
{
    //IMPLEMENTAR
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
        atualizar(*raiz);
    }
    //atualizar(*(raiz));
    balancear(*raiz);
}

/**
 * Funcao que recebe a raiz de uma BST e atualiza sua altura
 * e fator de balan�o.
 * Lembre que a altura das sub-�rvores direita e esquerda
 * não vão mudar, por isso a implementa�ão não é tão complicada.
 **/
void atualizar(struct noBst *no)
{
    //IMPLEMENTAR
    //cout << "atualizar " << no->val << endl;
    int alturaDireita = 0;
    if (no->dir != NULL)
    {
        atualizar(no->dir);
        alturaDireita = no->dir->altura + 1;

        //cout << "atualizar 1 if" << endl;
    }
    int alturaEsquerda = 0;
    if (no->esq != NULL)
    {
        atualizar(no->esq);
        alturaEsquerda = no->esq->altura + 1;

        //cout << "atualizar 2 if: " << alturaEsquerda << endl;
    }
    no->balanco = alturaDireita - alturaEsquerda;
    //cout << "balanco " << no->balanco << endl;

    if (no->balanco > 0)
    {
        no->altura = alturaDireita;
        //cout << "atualizar 3 if" << endl;
    }
    else
    {
        no->altura = alturaEsquerda;
        //cout << "atualizar 4 if" << endl;
    }
    //cout << "fim atualizar " << endl
    // << endl;
}
/**
 * Funcao que recebe a raiz de uma BST e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Dica: usar fator de balan�o do nó e de uma de suas sub-árvores
 * para descobrir qual é o caso.
 **/
struct noBst *balancear(struct noBst *no)
{
    //IMPLEMENTAR
    // if (no->balanco <= -1 && no->balanco >= 1)
    // {
    //     return no;
    // }
    if (no->balanco < -1)
    {
        // caso 1 ou 2
        if (no->esq->balanco <= 0)
        {
            //caso 1
            return rebalancearEsqEsq(no);
        }
        else
        {
            //caso 2
            return rebalancearEsqDir(no);
        }
    }
    if (no->balanco > 1)
    {
        //caso 3 ou 4
        if (no->dir->balanco >= 0)
        {
            //caso 3
            return rebalancearDirDir(no);
        }
        else
        {
            //caso 4
            return rebalancearDirEsq(no);
        }
    }
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota�ões
 * apropriadas para balancear uma árvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst *rebalancearEsqEsq(struct noBst *no)
{
    //IMPLEMENTAR
    return rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst *rebalancearEsqDir(struct noBst *no)
{
    //IMPLEMENTAR
    struct noBst *temp = rotacaoEsquerda(no->esq);
    no->esq = temp;
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst *rebalancearDirDir(struct noBst *no)
{
    //IMPLEMENTAR
    return rotacaoEsquerda(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst *rebalancearDirEsq(struct noBst *no)
{
    //IMPLEMENTAR
    struct noBst *temp = rotacaoDireita(no->dir);
    no->dir = temp;
    return no;
}

/**
 * Funcao que retorna o maior valor de uma árvore.
 * Mesma implementa��o da BST.
 **/
int max(struct noBst *raiz)
{
    //IMPLEMENTAR
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
 * Funcao que retorna o menor valor de uma �rvore.
 * Mesma implementa��o da BST.
 **/
int min(struct noBst *raiz)
{
    //IMPLEMENTAR
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
 * Funcao que retorna a altura de uma �rvore.
 * A altura de uma �rvore � dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 * Mesma implementa��o da BST.
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
        return altura_direita + 1;
    }
    else
    {
        return altura_esquerda + 1;
    }
}

struct noBst *noMinValor(struct noBst *no)
{
    struct noBst *aux = no;

    while (aux && aux->esq != NULL)
        aux = aux->esq;

    return aux;
}

/**
 * Funcao que recebe a raiz de uma �rvore, e
 * remove o n� que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho � passado por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� removido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de remover de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
struct noBst *remover(struct noBst *raiz, int val, int *tamanho)
{
    //IMPLEMENTAR
    if (raiz == NULL)
    {
        return raiz;
    }

    if (val < raiz->val)
        raiz->esq = remover(raiz->esq, val, tamanho);

    else if (val > raiz->val)
        raiz->dir = remover(raiz->dir, val, tamanho);

    else
    {
        // no folha
        if (raiz->esq == NULL && raiz->dir == NULL)
            return NULL;

        // no com apenas 1 filho
        else if (raiz->esq == NULL)
        {
            struct noBst *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL)
        {
            struct noBst *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // no com 2 filhos
        struct noBst *temp = noMinValor(raiz->dir);

        raiz->val = temp->val;

        raiz->dir = remover(raiz->dir, temp->val, tamanho);

        tamanho--;
    }
    atualizar(raiz);
    return raiz;
}

void imprimir(queue<struct noBst *> nosImpressao);

/**
* Fun��o que imprime a �rvore.
* Pode ser �til para depura��o.
**/
void imprimir(struct noBst *raiz)
{
    queue<struct noBst *> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBst *> nosImpressao)
{

    queue<struct noBst *> nosImpressaoProxNivel;

    while (!nosImpressao.empty())
    {
        struct noBst *noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL)
        {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL)
        {
            cout << to_string(noImpressao->val) << " | ";
        }
        else
        {
            cout << "N | ";
        }
    }
    cout << endl
         << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}