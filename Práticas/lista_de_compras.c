#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_NAME_SIZE 75

typedef enum Prioridade 
{
    BAIXA,
    MEDIA,
    ALTA
}Prioridade;

typedef struct Produto 
{
    char nome[MAX_PRODUCT_NAME_SIZE];
    float preco;
    enum Prioridade prioridade;
    struct Produto *proximo;
}Produto;

typedef struct 
{
    Produto * primeiro_produto;
    Produto * ultimo_produto;
    int tamanho;
    float preco_total;
}ListaDeCompras;

char * nivel_de_prioridade(Prioridade prioridade)
{
    switch (prioridade)
    {
        case BAIXA:
            return "Baixa";
        case MEDIA:
            return "Media";
        case ALTA:
            return "Alta";
    }
}

ListaDeCompras * criar_lista_de_compras()
{
    ListaDeCompras * nova = malloc(sizeof(ListaDeCompras));
    nova->primeiro_produto = NULL;
    nova->ultimo_produto = NULL;
    nova->tamanho = 0;
    nova->preco_total = 0.0;    
    return nova;
}

Produto * criar_produto(char nome[MAX_PRODUCT_NAME_SIZE], float preco, Prioridade prioridade)
{
    Produto *novo = malloc(sizeof(Produto));
    strcpy(novo->nome, nome);
    novo->preco = preco;
    novo->prioridade = prioridade;
    novo->proximo = NULL;

    return novo;
}

void add(ListaDeCompras *lista, Produto *produto, int pos)
{
    if (produto == NULL) return;

    
    if (lista->primeiro_produto == NULL) 
    {
        lista->primeiro_produto = produto;
        lista->ultimo_produto = produto;
    }
    else if (pos == 0) 
    {
        produto->proximo = lista->primeiro_produto;
        lista->primeiro_produto = produto;
    }
    else if (pos == lista->tamanho - 1) 
    {
        lista->ultimo_produto->proximo = produto;
        lista->ultimo_produto = produto;
        produto->proximo = NULL;
    } 
    else 
    {
        Produto *aux = lista->primeiro_produto;
        for (int i = 0; i < pos-1 ; i++) {
            aux = aux->proximo;
        }
        produto->proximo = aux->proximo;
        aux->proximo = produto;
    }

    lista->preco_total += produto->preco;
    lista->tamanho++;
}



Produto * remover(ListaDeCompras *lista, int pos)
{
    if (pos >= 0 && pos < lista->tamanho)
    {
        Produto *lixo = lista->primeiro_produto;
        if (pos == 0) 
        {
            lista->primeiro_produto = lista->primeiro_produto->proximo;
        } 
        else if (pos == lista->tamanho-1) 
        {
            Produto *aux = lixo;
            for (int i = 0; i < pos-1; i++) 
            {
                aux = aux->proximo;
            }
            lixo = lista->ultimo_produto;
            lista->ultimo_produto = aux;
            lista->ultimo_produto->proximo = NULL;
        } 
        else 
        {
            Produto *aux = lista->primeiro_produto;
            for (int i = 0; i < pos-1; i++) 
            {
                aux = aux->proximo;
            }
            lixo = aux->proximo;
            aux->proximo = lixo->proximo;
        }
        lista->tamanho--;
        lista->preco_total -= lixo->preco;
        Produto *tmp = criar_produto(lixo->nome, lixo->preco, lixo->prioridade);

        free(lixo);
        return tmp;
    }
    else 
    {
        return NULL;
    }
}


void exibir(ListaDeCompras *lista)
{
    Produto *aux = lista->primeiro_produto;

    if (aux == NULL)
    {
        printf("Lista de compras está vazia!\n");
        return;
    }

    do
    {
        printf("Nome do produto: %s | preco: %.2f R$ | Prioridade: %s\n", aux->nome, aux->preco, nivel_de_prioridade(aux->prioridade));
        aux = aux->proximo;
    }
    while (aux != NULL);

    printf("Fim da lista de compras!\n");
    printf("O total ficou por RS%.2f!\n", lista->preco_total);
}




