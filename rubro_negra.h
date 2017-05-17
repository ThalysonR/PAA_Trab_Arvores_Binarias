#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

typedef struct node{
	int verm;  //Vermelho = 1; Preto = 0.
	int chave;
	struct node *prox[2];
	}Node;
	
typedef struct arv{
	struct node *raiz;
	}Arv;
	
	
Node *remove_balanceia(Node *raiz,int dir,int *feito);
	
	
	
	
int e_verm(Node *raiz){
		return raiz != NULL && raiz->verm == 1;
	}
	
Node *rt_simples(Node *raiz,int dir){
		Node *aux = raiz->prox[!dir];
		
		raiz->prox[!dir] = aux->prox[dir];
		aux->prox[dir] = raiz;
		
		raiz->verm = 1;
		aux->verm = 0;
		
		return aux;
	}
	
Node *rt_dup(Node *raiz,int dir){
		raiz->prox[!dir] = rt_simples(raiz->prox[!dir],!dir);
		
		return rt_simples(raiz,dir);
	}
	
int rn_validar(Node *raiz){
		int esq,dir;
		
		if(raiz == NULL){
			return 1;
		}else{
			Node *n_esq = raiz->prox[0];
			Node *n_dir = raiz->prox[1];
			
			//Vermelhos seguidos
			if(e_verm(raiz)){
				if(e_verm(n_esq) || e_verm(n_dir)){
					puts("Violação Vermelha");
					return 0;
				}
			}
			esq = rn_validar(n_esq);
			dir = rn_validar(n_dir);
			
			//Árvore de busca binária inválida
			if((n_esq != NULL && n_esq->chave >= raiz->chave) || (n_dir != NULL && n_dir->chave <= raiz->chave)){
				puts("Violação: Árvore Binária inválida.");
				return 0;
			}
			
			//Altura preta diferente
			if(esq != 0 && dir != 0 && esq != dir){
				puts("Violação: Altura preta.");
				return 0;
			}
			
			//Contar só os nós pretos
			if(esq != 0 && dir != 0){
				return e_verm(raiz) ? esq : esq + 1;
			}else{
				return 0;
			}
		}
	}
	
Node *criaNo(int chave){
		Node *nv = malloc(sizeof *nv); //Cria nó vermelho (nv)
		
		if(nv != NULL){
			nv->chave = chave;
			nv->verm = 1;
			nv->prox[0] = nv->prox[1]  = NULL;
		}
		return nv;
	}
	
Arv *inicializArv(){
		Arv *avre = malloc(sizeof *avre);
		avre->raiz = NULL;
		return avre;
	}
	
	
void imprimeArv(Node *raiz){
		if(raiz->prox[0] != NULL)
		imprimeArv(raiz->prox[0]);
		printf("(%d)",raiz->chave);
		printf("(%c)\n",raiz->verm? 'v':'p');
		if(raiz->prox[1] != NULL)
		imprimeArv(raiz->prox[1]);
	}
	
void imprimir(Arv *avre){
		if(avre->raiz != NULL)
		imprimeArv(avre->raiz);
	}

Node *inserir_raiz(Node *raiz,int chave){
		if(raiz == NULL){
			raiz = criaNo(chave);
		}else if(chave != raiz->chave){
			int dir = raiz->chave < chave; //Determina direção a ser inserida. 1 = direita; 0 = esquerda
			
			raiz->prox[dir] = inserir_raiz(raiz->prox[dir],chave);
			
			if(e_verm(raiz->prox[dir])){
				if(e_verm(raiz->prox[!dir])){
					//Caso 1
					raiz->verm = 1;
					raiz->prox[0]->verm = 0;
					raiz->prox[1]->verm = 0;
				}else{
					//Casos 2 e 3
					if(e_verm(raiz->prox[dir]->prox[dir])){
						raiz = rt_simples(raiz,!dir);
					}else if(e_verm(raiz->prox[dir]->prox[!dir])){
						raiz = rt_dup(raiz,!dir);
					}
				}
			}
		}
		return raiz;
	}

int inserir(Arv *avre, int chave){
		avre->raiz = inserir_raiz(avre->raiz,chave);
		avre->raiz->verm = 0;
		
		return 1;
	}
	
Node *remove_balanceia(Node *raiz,int dir,int *feito){
		Node *p = raiz;
		Node *s = raiz->prox[!dir];
		
		if(e_verm(s)){
			raiz = rt_simples(raiz,dir);
			s = p->prox[!dir];
		}
		if(s != NULL){
			if(!e_verm(s->prox[0]) && !e_verm(s->prox[1])){
				if(e_verm(p)){
					*feito = 1;
				}
				p->verm = 0;
				s->verm = 1;
			}else{
				int aux = p->verm;
				int nova_raiz = (raiz == p);
				
				if(e_verm(s->prox[!dir])){
					p = rt_simples(p,dir);
				}else{
					p = rt_dup(p,dir);
				}
				p->verm = aux;
				p->prox[0]->verm = 0;
				p->prox[1]->verm = 0;
				
				if(nova_raiz){
					raiz = p;
				}else{
					raiz->prox[dir] = p;
				}
				*feito = 1;
			}
		}
		return raiz;
	}
	
Node *remover_raiz(Node *raiz, int chave, int *feito){
		if(raiz == NULL){
			*feito = 1;
		}else{
			int dir;
			if(raiz->chave == chave){
				if(raiz->prox[0] == NULL || raiz->prox[1] == NULL){
					Node *aux = raiz->prox[raiz->prox[0] == NULL];
					
					//Caso 0
					if(e_verm(raiz)){
						*feito = 1;
					}else if(e_verm(aux)){
						aux->verm = 0;
						*feito = 1;
					}
					free(raiz);
					
					return aux;
				}else{
					Node *sucessor = raiz->prox[0];
					
					while(sucessor->prox[1] != NULL){
						sucessor = sucessor->prox[1];
					}
					raiz->chave = sucessor->chave;
					chave = sucessor->chave;
				}
			}
			dir = raiz->chave < chave;
			raiz->prox[dir] = remover_raiz(raiz->prox[dir],chave,feito);
			
			if(!*feito){
				raiz = remove_balanceia(raiz,dir,feito);
			}
		}
		return raiz;
	}
	
int remover(Arv *avre,int chave){
		int feito = 0;
		
		avre->raiz = remover_raiz(avre->raiz,chave,&feito);
		
		if(avre->raiz != NULL){
			avre->raiz->verm = 0;
		}
		return 1;
	}
	


#endif
