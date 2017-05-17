#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

int main()
{
	Arv *rb = inicializArv();
	for(int i = 10; i>0; i--){
		inserir(rb,i);
	}
	imprimir(rb);
	rn_validar(rb->raiz);
	return 0;
}

