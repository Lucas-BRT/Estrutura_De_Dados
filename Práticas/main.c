#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_de_compras.c"

int main()
{
    ListaDeCompras * lista_da_seia = criar_lista_de_compras();

    Produto * sabao = criar_produto("Sabao", 10.00, ALTA);
    add(lista_da_seia, sabao, 0);

    Produto * macarrao = criar_produto("Macarrão", 20.00, ALTA);
    add(lista_da_seia, macarrao, 1);

    remover(lista_da_seia, 0);

    exibir(lista_da_seia);


    return 0;
}

