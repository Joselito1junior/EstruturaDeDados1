#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

// Tipo base dos elementos da lista
typedef struct elementos {
    char nome[50];
    int num;
} t_elemento;

// Estrutura da pilha
typedef struct pilha {
    t_elemento vetor[MAX];
    int topo;
} t_pilha;


//////FUNÇÔES DE MANIPULAÇÂO DA PILHA///////////

t_pilha criar();
int isVazia(t_pilha * pilha) ;
int isCheia(t_pilha * pilha) ;
t_elemento getElementoTopo(t_pilha * pilha);
t_elemento pop(t_pilha * pilha);
int push(t_pilha *pilha, t_elemento valor);

////////////FUNÇOES DE MANIPULAÇÃO/////////////

void mostra_placas(t_pilha * estacionamento);
void saida_carro(t_pilha * estacionamento);
int menu_principal(t_pilha * estacionamento);

/////////////FUNÇÕES PRINCIPAIS////////////////

int main()
{
	t_pilha estacionamento;
	t_elemento nome_aux;

	int opcao = 0;

	estacionamento = criar();

	do{
		if(!isCheia(&estacionamento))
		{
			opcao = menu_principal(&estacionamento);
			if(opcao == -1)
				break;

			if(opcao)
			{
				printf("Digite a placa: ");
				scanf("%s", &nome_aux.nome);
				push(&estacionamento, nome_aux);
				mostra_placas(&estacionamento);
			}
			else
				saida_carro(&estacionamento);
		}
		else
		{
			printf("\n===============================\n");
			printf("      Estacionamento lotado      \n");
			printf("===============================\n");
			saida_carro(&estacionamento);
		}

	}while(opcao != -1);
	return 0;
}


//////FUNÇÔES DE MANIPULAÇÂO DA PILHA///////////

/**
 * Cria uma nova pilha, aloca a sua regiao de memoria,
 * inicializa o topo, e retorna a pilha criada.
 * 
 * @return Pilha inicializada
 */
t_pilha criar() {
    t_pilha pilha;

    pilha.topo = -1;

    return pilha;
}

/**
 * Verifica se a pilha esta vazia ou nao.
 * 
 * @param pilha ponteiro para a pilha, a pilha ja deve ter sido inicializada
 *
 * @return Verdadeiro (1) se a pilha estiver vazia, ou falso (0) caso contrario.
 */
int isVazia(t_pilha * pilha) {
    return (pilha->topo == -1);
}


/**
 * Verifica se a pilha esta cheia ou nao.
 * 
 * @param pilha ponteiro para a pilha, a pilha ja deve ter sido inicializada
 *
 * @return Verdadeiro (1) se a pilha estiver cheia, ou falso (0) caso contrario.
 */
int isCheia(t_pilha * pilha) {
    return (pilha->topo == MAX-1);
}

/**
 * Obter o elemento do topo da pilha (sem eliminar)
 * 
 * @param pilha ponteiro para a pilha, a pilha ja deve ter sido inicializada
 *
 * @return o elemento desejado, caso a posicao seja invalida retorna vazio.
 */    
t_elemento getElementoTopo(t_pilha * pilha)
{
    t_elemento vazio = { "" } ;

    if (isVazia(pilha))
        return vazio; // erro
    else
        return pilha->vetor[pilha->topo];
}

/**
 * Remove o elemento do topo da pilha (desempilhar), retornando o elemento removido
 * 
 * @param pilha ponteiro para a pilha, a pilha ja deve ter sido inicializada
 *
 * @return Uma copia do elemento do topo.
 */
t_elemento pop(t_pilha * pilha)
{
    t_elemento vazio = { "" };

    if (isVazia(pilha))
        return vazio; // erro
    else
        return pilha->vetor[pilha->topo--];
}

/**
 * Inserir um novo elemento no topo da pilha (empilhar)
 * 
 * @param pilha ponteiro para a pilha, a pilha ja deve ter sido inicializada
 * @param dado  elemento a ser inserido na pilha
 *
 * @return Falso(0) se a posição for invalida ou se a pilha estiver cheia, caso contrario, retorna Verdadeiro(1)
 */
int push(t_pilha *pilha, t_elemento valor)
{
    if (isCheia(pilha))
        return 0; // erro

    pilha->vetor[++pilha->topo] = valor;

    return 1; // sucesso
}



void saida_carro(t_pilha * estacionamento)
{
	int opcao = 0;

	printf("\nO dono do ultimo carro deseja sair? \n");
	printf("1 - SIM\n");
	printf("0 - NAO\n");
	printf("Digite: ");
	scanf("%d", &opcao);

	if(opcao && !isVazia(estacionamento))
	{
		int carro_saiu = estacionamento->topo;
		printf("\nO carro que saiu foi:  %s\n", estacionamento->vetor[carro_saiu].nome);
		pop(estacionamento);
	}	
	else if(opcao && isVazia(estacionamento))
		printf("\nNao ha carros estacionados\n");

	mostra_placas(estacionamento);
}



void mostra_placas(t_pilha * estacionamento)
{
	int i = 0;

	printf("===============================\n");
	printf("       Placas atuais		   \n");
	printf("===============================\n");

	for (i = 0; i < estacionamento->topo + 1; i++)
	{
		printf("%d - %s\n", i + 1, estacionamento->vetor[i].nome);
	}
	printf("===============================\n");	
}


int menu_principal(t_pilha * estacionamento)
{
	int opcao = 0;

	printf("\n===============================");
	printf("\n     Ha %d vagas\n", MAX - (estacionamento->topo + 1));
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