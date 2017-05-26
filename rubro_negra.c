#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubro_negra.h"
#define rnd_max 30000

int aleatorio(int n){
		return rand() % n;
	}

void execucao(clock_t t,char op[20]){
		double tempo_exec = ((double)t)/CLOCKS_PER_SEC;
		printf("Tempo de %s: %.4f segundos\n",op,tempo_exec);
	}

void insere_certo(Arv *rb,Node *raiz){
		if(raiz->prox[0] != NULL)
		insere_certo(rb,raiz->prox[0]);
		inserir(rb,raiz->chave);
		if(raiz->prox[1] != NULL)
		insere_certo(rb,raiz->prox[1]);
	}

void tempos(Arv *rb,int n,int testes){
	clock_t t[5];
	int estatico[testes], contador = 89,i = 0;
	Arv *aux = inicializArv();
	
	
	printf("Tratando repeticoes...");
	for(i = 0; i < testes; i++){
		estatico[i] = contador;
		if( n < rnd_max)
			contador += aleatorio(n*10);
		else
			contador += aleatorio(n);
	}
	
		if(n < rnd_max){
			
		
			for(i = 0; i < testes; i++){
				inserir(aux,estatico[i]);
			}
			
			for(i = 0; i < n-testes; i++){
				if(!inserir(aux,aleatorio(n))){
					i--;
				}
			}
		}
		
		printf("Pressione enter:");
		getchar();
		
		//INSERCAO
		t[0] = clock();
		if(n < rnd_max)
			insere_certo(rb,aux->raiz);
		else
			for(i = 0; i < n; i++){
				inserir(rb,i);
			}
		t[0] = clock() - t[0];
		execucao(t[0],"insercao");
		printf("Numero de nos: %d\nPressione enter:",contArv(rb->raiz));
		getchar();
		for(int i = 0; i < testes; i++){
		//BUSCA EXISTENTE
		t[1] = clock();
		buscar(rb,estatico[i]);
		t[1] = clock() - t[1];
		execucao(t[1],"busca existente");
		
		//BUSCA NAO EXISTENTE
		t[2] = clock();
		buscar(rb,n*10+1);
		t[2] = clock() - t[2];
		execucao(t[2],"busca nao existente");
		
		//REMOCAO EXISTENTE
		t[3] = clock();
		remover(rb,estatico[i]);
		t[3] = clock() - t[3];
		execucao(t[3],"remocao existente");
		
		//REMOCAO NAO EXISTENTE
		t[4] = clock();
		remover(rb,n*10+1);
		t[4] = clock() - t[4];
		execucao(t[4],"remocao nao existente");
		printf("\n\n\n");
		}
		rn_validar(rb->raiz);
		printf("Numero de nos: %d\n",contArv(rb->raiz));
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

