/*
	author: Joselito_Junior
	date: 14/10/2017
	version: 1.0

	Descrição: Essa uma implementação simples de uma fila sequencial circular
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

// Tipo base dos elementos da lista
typedef struct elementos{
	char nome[50];
}t_elemento;

typedef struct fila{
	t_elemento vetor[MAX];
	int inicio;
	int fim;
	int qtd_elements;
}t_fila;

//////FUNÇÔES DE MANIPULAÇÂO DA PILHA///////////

t_fila criar_fila();
int is_vazia_fila(t_fila * fila);
int is_cheia_fila(t_fila * fila);
int inserir_fila(t_fila * fila, t_elemento elemento);
t_elemento remover_fila(t_fila * fila);
void exibir_fila(t_fila * fila);
int exibicao_ordenada_fila(t_fila * fila);

/////////////FUNÇOES  DE GERENCIAMENTO//////////
int menu_principal(t_fila * fila);

int saida_fila(t_fila * fila)
{
	int opcao = 0;
	t_elemento chamado;

	printf("\nDeseja chamar o primeiro da fila? \n");
	printf("1 - SIM\n");
	printf("0 - NAO\n");
	printf("Digite: ");
	scanf("%d", &opcao);

	if(opcao && !is_vazia_fila(fila))
	{
		chamado = remover_fila(fila);
		printf("%s saiu da fila. \n", chamado.nome);
	}	
	//else if(opcao && is_vazia_fila(fila));


	exibir_fila(fila);
	exibicao_ordenada_fila(fila);
}
////////////////FUNÇÃO PRINCIPAL///////////////

int main()
{
	t_fila fila;
	t_elemento elemento;
	int opcao = 0;

	fila = criar_fila();

	do{
		if(!is_cheia_fila(&fila))
		{
			opcao = menu_principal(&fila);
			if(opcao == -1)
				break;

			if(opcao)
			{
				printf("Digite um identificador: ");
				scanf("%s", &elemento);
				inserir_fila(&fila, elemento);
				exibir_fila(&fila);
				exibicao_ordenada_fila(&fila);
			}
			else

				if(is_vazia_fila(&fila))
					printf("Nao ha ninguem na fila\n");
				else
					saida_fila(&fila);
		}
		else
		{
			printf("\n===============================\n");
			printf("           FILA LOTADA         \n");
			printf("===============================\n");
			saida_fila(&fila);
		}

	}while(opcao != -1);

	return 0;
}


//////FUNÇÔES DE MANIPULAÇÂO DA PILHA///////////

/**
 * Cria uma nova fila, aloca a sua regiao de memoria,
 * inicializa o inicio, fim e a quantidade de elementos.
 * Por fim, retorna a fila criada.
 *
 * @return Fila inicializada
 */
t_fila criar_fila()
{
	t_fila fila;
	int i = 0;

	fila.inicio = 0;
	fila.fim =-1;
	fila.qtd_elements = 0;

	for(i = 0; i < MAX; i++)
		strcpy(fila.vetor[i].nome, "\0");

	return fila;
}

/**
 * Verifica se a fila esta vazia ou nao.
 *
 * @param fila ponteiro para a fila, a fila ja deve ter sido inicializada
 *
 * @return Verdadeiro (1) se a fila estiver vazia, ou falso (0) caso contrario.
 */
int is_vazia_fila(t_fila * fila)
{
	return(fila->qtd_elements == 0);
}

/**
 * Verifica se a fila esta cheia ou nao.
 *
 * @param fila ponteiro para a fila, a fila ja deve ter sido inicializada
 *
 * @return Verdadeiro (1) se a fila estiver cheia, ou falso (0) caso contrario.
 */
int is_cheia_fila(t_fila * fila)
{
	return(fila->qtd_elements == MAX);
}


/**
 * Insere um elemento (valor) no final da fila.
 * 
 * @param fila ponteiro para a fila, a fila ja deve ter sido inicializada
 * @param valor elemento a ser inserido na fila
 *
 * @return Falso(0) se a fila estiver cheia, caso contrario, retorna Verdadeiro(1)
 */
int inserir_fila(t_fila * fila, t_elemento elemento)
{
	if(is_cheia_fila(fila))
		return 0;

	//Entra nessa parte caso a fila não esteja cheia
	(fila->qtd_elements)++;
	fila->fim = (fila->fim + 1) % MAX;
	fila->vetor[fila->fim] = elemento;
	return 1;
}

/**
 * Remove um elemento do inicio da fila.
 * 
 * @param fila ponteiro para a fila, a fila ja deve ter sido inicializada
 *
 * @return o elemento removido.
 */
t_elemento remover_fila(t_fila * fila)
{
	t_elemento elemento = {"\0"};

	if(is_vazia_fila(fila))
		return elemento;

	elemento = fila->vetor[fila->inicio];
	strcpy(fila->vetor[fila->inicio].nome, "\0");
	(fila->qtd_elements)--;
	fila->inicio = (fila->inicio + 1) % MAX;
	return elemento;
}

/**
 * Exibe todos os elementos da fila
 *
 * @param fila ponteiro para a fila, a fila ja deve ter sido inicializada
 */
void exibir_fila(t_fila * fila) {
    int i;
    if (is_vazia_fila(fila)) {
        printf("Fila vazia\n");
        return;
    }

    printf("\nExibindo ordem da fila circular:\n");
    printf("inicio: %d\n", fila->inicio);
    printf("fim:    %d\n", fila->fim);
    for (i=0 ; i<MAX ; i++) {
        printf("%d::%s\n", i, fila->vetor[i].nome);
    }
}

int exibicao_ordenada_fila(t_fila * fila)
{
	int i = 0;

	if(is_vazia_fila(fila))
		return 0;

	printf("\nExibindo fila circular ordenada:\n");
	for(i = 0; i <fila->qtd_elements; i++)
		printf("%d::%s\n", i + 1, fila->vetor[(fila->inicio + i) % MAX].nome);

	//Metodo do professor
	//for (i = fila->inicio; i != fila->fim + 1; i = (i + 1) % MAX)
    //    printf("%d\t", fila->vetor[i]);

}

//////FUNÇÕES DE GERENCIAMENTO DA FILA////////

int menu_principal(t_fila * fila)
{
	int opcao = 0;

	printf("\n===============================\n");

	printf("Deseja entrar ou sair \n");
	printf("1 - ENTRAR\n");
	printf("0 - SAIR \n");
	printf("-1 - EXIT PROGRAMA\n");
	printf("===============================\n");
	printf("Digite: ");
	scanf("%d", &opcao);
	printf("===============================\n");

	return opcao;
}

