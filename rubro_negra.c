#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

int main()
{
	Arv *rb = inicializArv();
	if(inserir(rb,5)){
	printf("Sucexo! -> %d",rb->raiz->chave);
	}
	else
	puts("Falhou!");
	return 0;
}

