/*
	author: Joselito_Junior
	date: 14/10/2017
	version: 1.0

	Descrição: Essa uma implementação simples de uma fila encadeada circular
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50

typedef struct elementos{
	char nome[TAM_NOME];
}t_elemento;

typedef struct no{
	t_elemento dado;
	struct no * prox;
}t_no;

typedef struct fila{
	t_no * inicio;
	int qtd_elementos;
	t_no * fim;
}t_fila;

//////FUNÇÕES DE MANIPULAÇÃO DA FILA ENCADEADA CIRCULAR//////
t_fila * cria_cabeca_fila_enc();
t_no * cria_no_fila_enc();
int is_vazia_fila_enc(t_fila * fila);
int inserir_fila_enc(t_fila * fila, t_elemento elemento);
t_elemento remover_fila_enc(t_fila * fila);

////FUNÇÕES DE GERENCIAMENTO DA FILA ENCADEADA/////
int menu_principal();
int exibe_fila(t_fila * fila);
int saida_fila(t_fila * fila);

//////////////////FUNÇÃO PRINCIPAL/////////////////

int main()
{
	t_fila * fila;
	t_elemento elemento;

	int opcao = 0;

	fila = cria_cabeca_fila_enc();

	
	do{
		opcao = menu_principal(&fila);

		if(opcao == -1)
			break;

		if(opcao)
		{
			printf("Digite um identificador: ");
			scanf("%s", &elemento);
			inserir_fila_enc(fila, elemento);
		}
		else
		{
			if(is_vazia_fila_enc(fila))
				printf("Nao ha ninguem na fila\n");
			else
				saida_fila(fila);

		}
		exibe_fila(fila);
	}while(opcao != -1);
	
	return 0;
}

//////FUNÇÕES DE MANIPULAÇÃO DA FILA ENCADEADA CIRCULAR//////
/**
 * Cria uma fila vazia, ou seja um no cabeca.
 * inicializa os ponteiros ini e fim para NULL,
 * e seta quant_element para zero.
 * 
 * @return no cabeca alocado e inicializado
 */

t_fila * cria_cabeca_fila_enc()
{
	t_fila * fila = (t_fila*)malloc(sizeof(t_fila));

	if(fila)
	{
		fila->qtd_elementos = 0;
		fila->inicio = NULL;	
		fila->fim = NULL;
	}

	return fila;
}

/**
 * Cria um novo no, aloca a sua regiao de memoria,
 * inicializa o ponteiro prox, e retorna o ponteiro para a pilha criada.
 * 
 * @return No alocada e inicializada
 */

t_no * cria_no_fila_enc()
{
	t_no * no = (t_no*) malloc(sizeof(t_no));

	//Verifica se o nó existe
	if(no)
	{
		no->prox = NULL;
		strcpy(no->dado.nome, "\0");
	}

	return no;
}

/**
 * Verifica se a fila esta vazia ou nao. Isto so acontece quando ela eh nula
 * 
 * @param fila ponteiro para a fila
 *
 * @return Verdadeiro (1) se a fila estiver vazia, ou falso (0) caso contrario.
 */

int is_vazia_fila_enc(t_fila * fila)
{
	return(!fila->qtd_elementos);
}

/**
 * Insere um elemento (valor) no fim da fila.
 * 
 * @param fila ponteiro para a fila
 * @param valor  elemento a ser inserido na fila
 *
 * @return Falso(0) se a fila estiver cheia, caso contrario, retorna Verdadeiro(1).
*/
int inserir_fila_enc(t_fila * fila, t_elemento elemento)
{
	t_no * novo;
	novo = cria_no_fila_enc();

	if(novo == NULL)
		return 0; //Erro: memória insuficiente

	novo->dado = elemento;

	if(is_vazia_fila_enc(fila))
		fila->inicio = novo;
	else
		fila->fim->prox = novo;

	fila->fim = novo;
	fila->qtd_elementos++;

	return 1;
}


/**
 * Remove um elemento do inicio da fila.
 * 
 * @param fila ponteiro para a fila, a fila ja deve ter sido inicializada
 *
 * @return o elemento removido.
 */
t_elemento remover_fila_enc(t_fila * fila)
{
	t_no * aux;
	t_elemento valor = {" "};

	if(is_vazia_fila_enc(fila))
		return valor;

	valor = fila->inicio->dado;

	if(fila->inicio == fila->fim)
		fila->fim = NULL;

	aux = fila->inicio;
	fila->inicio = fila->inicio->prox;
	
	free(aux);
	fila->qtd_elementos--;
	return valor;
}

//////FUNÇÕES DE GERENCIAMENTO DA FILA////////

int menu_principal()
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

int exibe_fila(t_fila * fila)
{
	int i = 0;
	t_no * no_aux;

	if(is_vazia_fila_enc(fila))
		return 0;

	no_aux = fila->inicio;
	printf("\nExibindo fila de elementos em sequencia:\n");

	do
	{
		printf("%d::%s\n", ++i, no_aux);
		no_aux = no_aux->prox;
	}while(no_aux != NULL);
}

int saida_fila(t_fila * fila)
{
	int opcao = 0;
	t_elemento chamado;

	printf("\nDeseja chamar o primeiro da fila? \n");
	printf("1 - SIM\n");
	printf("0 - NAO\n");
	printf("Digite: ");
	scanf("%d", &opcao);

	if(opcao)
	{
		chamado = remover_fila_enc(fila);
		printf("%s saiu da fila. \n", chamado.nome);
	}

	exibe_fila(fila);
}