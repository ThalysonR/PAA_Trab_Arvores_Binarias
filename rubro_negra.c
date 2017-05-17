#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rubro_negra.h"

int aleatorio(){
		return rand() % 65536;
	}

void execucao(clock_t t,char op[20]){
		double tempo_exec = ((double)t)/CLOCKS_PER_SEC;
		printf("Tempo de %s: %.4f segundos\n",op,tempo_exec);
	}

int main(int argc, char **argv)
{
	Arv *rb = inicializArv();
	clock_t t[5];
	int n = atoi(argv[1]);
	srand(time(NULL));
	/*for(int i = 10; i>0; i--){
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
	srand(time(NULL));
	for(int i = 0; i < 10; i++){
		printf("%d\n",rand());
	}*/
	
	//INSERCAO
	t[0] = clock();
	inserir(rb,89);
	for(int i = 0; i < n; i++){
		inserir(rb,aleatorio());
	}
	t[0] = clock() - t[0];
	execucao(t[0],"insercao");
	
	//BUSCA EXISTENTE
	t[1] = clock();
	buscar(rb,89);
	t[1] = clock() - t[1];
	execucao(t[1],"busca existente");
	
	//BUSCA NAO EXISTENTE
	t[2] = clock();
	buscar(rb,65536);
	t[2] = clock() - t[2];
	execucao(t[2],"busca nao existente");
	
	//REMOCAO EXISTENTE
	t[3] = clock();
	remover(rb,89);
	t[3] = clock() - t[3];
	execucao(t[3],"remocao existente");
	
	//REMOCAO NAO EXISTENTE
	t[4] = clock();
	remover(rb,65536);
	t[4] = clock() - t[4];
	execucao(t[4],"remocao nao existente");
	return 0;
}

