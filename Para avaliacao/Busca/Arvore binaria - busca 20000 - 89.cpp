#include<stdio.h>
#include<stdlib.h>

#define N        20001
#define VALIDO   1
#define INVALIDO 0
#include <time.h>

typedef struct NoArvore
{
        int dado;
        struct NoArvore *esquerda;
        struct NoArvore *direita;

}NoArvore;

NoArvore* BuscarMenorValor(NoArvore *noh)
{
        if(noh==NULL)
        {
                /* Sem elementos na �rvore */
                return NULL;
        }
        if(noh->esquerda) /* Desce pela esquerda para achar o menor valor */
                return BuscarMenorValor(noh->esquerda);
        else 
                return noh;
}
NoArvore* BuscarMaiorValor(NoArvore *noh)
{
        if(noh==NULL)
        {
                /* Sem valores na �rvore */
                return NULL;
        }
        if(noh->direita) /* Desce pela direita para achar o maior valor */
                BuscarMaiorValor(noh->direita);
        else 
                return noh;
}

NoArvore * Inserir(NoArvore *noh,int dado)
{
        if(noh==NULL)
        {
                NoArvore *temp;
                temp = (NoArvore *)malloc(sizeof(NoArvore));
                temp -> dado = dado;
                temp -> esquerda = temp -> direita = NULL;
                return temp;
        }

        if(dado >(noh->dado))
        {
                noh->direita = Inserir(noh->direita,dado);
        }
        else if(dado < (noh->dado))
        {
                noh->esquerda = Inserir(noh->esquerda,dado);
        }
        /* N�o fa�a nada, caso o dado j� esteja na �rvore */
        return noh;

}

NoArvore *Remover(NoArvore *noh, int dado)
{
        NoArvore *temp;
        if(noh==NULL)
        {
                printf("Valor nao encontrado");
        }
        else if(dado < noh->dado)
        {
                noh->esquerda = Remover(noh->esquerda, dado);
        }
        else if(dado > noh->dado)
        {
                noh->direita = Remover(noh->direita, dado);
        }
        else
        {
                /* Remover este n� e substituir tanto com o menor valor na direita ou ent�o com o maior valor da esquerda. */
                if(noh->direita && noh->esquerda)
                {
                        /* Substituir pelo menor valor na direita */
                        temp = BuscarMenorValor(noh->direita);
                        noh -> dado = temp->dado; 
                        /* Remover o no utilizado, uma vez que substituimos com outro n�. */
                        noh -> direita = Remover(noh->direita,temp->dado);
                }
                else
                {
                        /* Se tiver somente um ou zero filhos, remover diretamente da �rvore e conectar o pai ao filho. */
                        temp = noh;
                        if(noh->esquerda == NULL)
                                noh = noh->direita;
                        else if(noh->direita == NULL)
                                noh = noh->esquerda;
                        free(temp); 
                }
        }
        return noh;

}

NoArvore *Busca(NoArvore *noh, int dado)
{
        if(noh==NULL)
        {
                /* Se o valor n�o for encontrado */
                return NULL;
        }
        if(dado > noh->dado)
        {
                /* Busca na direita */
                return Busca(noh->direita,dado);
        }
        else if(dado < noh->dado)
        {
                /* Busca na esquerda */
                return Busca(noh->esquerda,dado);
        }
        else
        {
                /* Valor encontrado */
                return noh;
        }
}



int main()
{
	


	NoArvore *raiz = NULL;
	
	 printf("Gerando 20000 valores aleatorios para inserir na arvore:\n\n");
 	 int i, j, status;
     int A[N];
    
    srand(time(NULL));

    for (i = 1; i < N; i++) {
       do {
          A[i] = rand() % N;
          status = VALIDO;
          for (j = 1; j < i; j++)
             if (A[i] == A[j])
                status = INVALIDO;
       } while (status == INVALIDO);   
       //printf("%d ", A[i]);
 
   	
       
    }
    
    printf("Valores gerados!\n\n");
    
    
	//Inser��o:
	for(i = 1; i < N; i++){
		raiz = Inserir(raiz, A[i]);
	}
    
    //Busca:
    double t;
	t = clock();
	
	NoArvore * temp;
  temp = Busca(raiz,89);
        if(temp==NULL)
        {
                printf("Valor 89 nao encontrado\n");
        }
        else
        {
                printf("Valor 89 encontrado\n");
        }

 t = (clock() - t)/CLOCKS_PER_SEC/1000;
 printf("Tempo de busca: %10f milissegundos\n",t);
 
}
