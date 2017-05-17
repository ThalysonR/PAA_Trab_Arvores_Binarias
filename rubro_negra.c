#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

int main(int argc, char **argv)
{
	Arv *rb = inicializArv();
	for(int i = 10; i>0; i--){
		inserir(rb,i);
	}
	imprimir(rb);
	rn_validar(rb->raiz);
	printf("\n\n\n");
	for(int i = 10;i>0; i = i-3){
		remover(rb,i);
	}
	imprimir(rb);
	rn_validar(rb->raiz);
	return 0;
}

