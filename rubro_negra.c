#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubro_negra.h"

int aleatorio(){
		return rand() % 65536;
	}

void execucao(clock_t t,char op[20]){
		double tempo_exec = ((double)t)/CLOCKS_PER_SEC;
		printf("Tempo de %s: %.4f segundos\n",op,tempo_exec);
	}

void tempos(Arv *rb,int n,int testes){
	clock_t t[5];
	int estatico[testes], contador = 89;
	for(int i = 0; i < testes; i++){
		estatico[i] = contador;
		contador += aleatorio();
	}
	
	
		//INSERCAO
		t[0] = clock();
		for(int i = 0; i < testes; i++){
			inserir(rb,estatico[i]);
		}
		
		for(int i = 0; i < n-testes; i++){
			inserir(rb,aleatorio());
		}
		t[0] = clock() - t[0];
		execucao(t[0],"insercao");
		system("PAUSE");
		for(int i = 0; i < testes; i++){
		//BUSCA EXISTENTE
		t[1] = clock();
		buscar(rb,estatico[i]);
		t[1] = clock() - t[1];
		execucao(t[1],"busca existente");
		
		//BUSCA NAO EXISTENTE
		t[2] = clock();
		buscar(rb,65536);
		t[2] = clock() - t[2];
		execucao(t[2],"busca nao existente");
		
		//REMOCAO EXISTENTE
		t[3] = clock();
		remover(rb,estatico[i]);
		t[3] = clock() - t[3];
		execucao(t[3],"remocao existente");
		
		//REMOCAO NAO EXISTENTE
		t[4] = clock();
		remover(rb,65536);
		t[4] = clock() - t[4];
		execucao(t[4],"remocao nao existente");
		printf("\n\n\n");
		}
	}

int main(int argc, char **argv)
{
	Arv *rb = inicializArv();
	
	int n = atoi(argv[1]),testes = 1;
	if(argc == 3){
	testes = atoi(argv[2]);
	}
	srand(time(NULL));
	tempos(rb,n,testes);	
	
	return 0;
}

