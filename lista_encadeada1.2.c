/////////////////////////////////////////////Lista Encadeada
/*----------------------------------------------------------------------------------
	Author: Joselito Ferreira Melo Junior
	Data: 08/10/17
	Versão: 1.0
   	Funcionalidade: Implementação de uma lista encadeada usando linguagem C

    --------------------------------------------------------------------------------	
	| Processos | Descrição
	---------------------------------------------------------------
	Finalizados:| Funções de Manipulação da lista
				| Gerenciamento de remoção
				| Telas de interface com usuário
				| Gerenciamento de Inserção
				| Gerenciamento de pesquisa na lista
				| Gerenciamento de tamanho da lista (Vazia / Cheia / Tamanho total)
	---------------------------------------------------------------
	Finalizando:| 
    ---------------------------------------------------------------				
	A finalizar:| 
				| 
				| 
	-------------------------------------------------------------------------------
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NOME_NAO_ENCONTRADO -1;

typedef struct Elemento{
	char nome[100];
}t_elemento;

typedef struct no{
	t_elemento dado;
	struct no * prox;
}t_no;

////////////////////////////////////////////////
//////////FUNÇÕES DA LISTA ENCADEADA////////////

t_no * cria_no_encad(); 									//Cria um novo nó na lista
int is_vazia_encad(t_no * lista);							//Verifica se a lista está vazia//
int get_tamanho_encad(t_no * lista);						//Verifica o tamanho da lista atual//
t_no * get_no_encad(t_no * lista, int pos);					//Retorna um no da lista
int inserir_encad(t_no ** lista, int pos, t_elemento dado);	//Inseri um novo no na lista vazia ou já em uso
t_elemento * get_elemento_encad(t_no * lista, int pos);		//retorna um elemento de um no de acordo com a posição passada
int compara_encad(t_elemento dado1, t_elemento dado2);		//Comparara um elemento passado pelo parametro com um existente na lista
int get_posicao_encad(t_no * lista, t_elemento dado);		//Retorna a posição de um elemento passado como parametro
int remover_encad(t_no ** lista, int pos);

////////////////////////////////////////////////
////////////FUNÇÕES DE MANIPULAÇÃO//////////////

int menu_principal();							//Tela do Menu Principal
int menu_remover_nome();						//Tela de opção para remover por nome ou por numero
t_elemento menu_pede_nome(t_elemento * dado);	//Tela onde é inserido o nome para remoção
int menu_pede_numero();							//Tela onde é inserido o numero para remoção
int remove_no(int opcao, t_no * lista);			//Função que gerencia a remoção de um no
void menu_tamanho_lista(t_no * lista);
int menu_lista_nomes(t_no * lista);
t_elemento menu_inserir_dados();
t_elemento menu_busca_nome();

////////////////////////////////////////////////
//////////////////PRINCIPAL/////////////////////

int main()
{
	t_no * lista = NULL;
	t_elemento novo_dado;
	int opcao = 0;
	int resultado = 0;

	for(;;)
	{
		switch(menu_principal())
		{
			case 1: menu_tamanho_lista(lista);
					break;

			case 2: novo_dado = menu_inserir_dados();
					inserir_encad(&lista, get_tamanho_encad(lista), novo_dado);
					break;

			case 3: novo_dado = menu_busca_nome();
					resultado = get_posicao_encad(lista, novo_dado);

					if (resultado < 0)
						printf("|O nome nao esta cadastrado");
					else
						printf("|O nome encontra-se na lista na posicao: %d", resultado + 1);//Soma 1 ao valor retornado para que o indice 
					break;																	 //que é visto pelo usuário comece em 1

			case 4: menu_lista_nomes(lista);
					break;

			case 5: resultado = menu_remover_nome(); //Remover pelo nome ou pelo numero?
					resultado = remove_no(resultado, lista); //Faz o tratamento para retornar a opcao do anterior seja excluir por nome ou por número
					remover_encad(&lista, resultado);//Faz a remoção
					break;

			case 99: return 0;

			default: printf("Opcao inválida");
		}
	opcao = 0;
	resultado = 0;
	}
}

///////////////////////////////////////////////

t_no * cria_no_encad()
{
	t_no * no = (t_no*) malloc(sizeof(t_no));

	if(no)
	{
		strcpy(no->dado.nome, "\0");
		no->prox = NULL;
	}
	return no;
}

int is_vazia_encad(t_no * lista)
{
	return(lista == NULL);
}

int get_tamanho_encad(t_no * lista)
{
	int n = 0;

	while(lista != NULL)
	{
		lista = lista->prox;
		n++;
	}
	return n;
}

t_no * get_no_encad(t_no * lista, int pos)
{
	int n = 0;

	if(pos < 0)
		return 0;

	while(lista != NULL)
	{
		if(n == pos)
			return lista;
		lista = lista -> prox;
		n++;
	}
	return 0;
}


int inserir_encad(t_no ** lista, int pos, t_elemento dado)
{
	t_no * novo_no = NULL;
	t_no * p = NULL;

	if(*lista == NULL)
	{
		novo_no = cria_no_encad();//Cria o espaço necessário para um novo no
		if(novo_no == NULL) //Caso não tenha sido criado o espaço 
			return 0; //erro 0: Memória insuficiente
		
		novo_no->dado = dado;
		novo_no->prox = NULL;
		*lista = novo_no;
		return 1;
	}

	p = get_no_encad(*lista, pos - 1);
	
	if(p == NULL)
		return 2;
	
	novo_no = cria_no_encad();//Cria o espaço necessário para um novo no
	novo_no->dado = dado; //insere o dado enviado pelo usuário no t_elemento de novo_no
	novo_no->prox = p->prox; //Insere o endereço do no que se encontra na posição buscada
	p->prox = novo_no;
	return 1;
}

t_elemento * get_elemento_encad(t_no * lista, int pos)
{
	t_no * no = get_no_encad(lista, pos);
	if(no != NULL)
		return &(no->dado);
	else
		return NULL;
}

int compara_encad(t_elemento dado1, t_elemento dado2)
{
	return strcmp(dado1.nome, dado2.nome);
}

int get_posicao_encad(t_no * lista, t_elemento dado)
{
	int n = 0;

	while(lista != NULL)
	{
		if(!compara_encad(lista->dado, dado))
			return n;
		lista = lista->prox;
		n++;
	}

	return NOME_NAO_ENCONTRADO;
}

int remover_encad(t_no ** lista, int pos)
{
	t_no * anterior = NULL;
	t_no * p = NULL;

	if(is_vazia_encad(*lista))
		return 0;
	
	if(pos < 0)
		return 0;

	if(pos == 0)
	{
		p = *lista;//Guarda o endereço do primeiro elemento para ralizar a liberação do espaço da memória.
		*lista = p->prox; //Joga o valor que estava contido no prox de *lista para ela mesma, ou seja armazena em lista o valor null 
	}		
	else
	{
		anterior = get_no_encad(*lista, pos - 1); //Retorna um elemento antes do elemento que deve ser excluido


		if(anterior  == NULL) //Se o valor recebido pela função anterior for null 
			return 0; //retorna que a posição não existe
		p = anterior->prox; //Se não, armazena o endereço do nó que será excluido dentro da variável p

		if(p == NULL) //Se o endereço é igual a null
			return 0;	//Retorna 0
		anterior->prox = p->prox;
	}
	free(p);
	return 1;
}

///////////////////////////////////////////////////////////

int menu_principal()
{
	int opcao = 0;

	printf("\n=================================== \n");
	printf("=    LISTA ENCADEADA FUNCIONAL    =\n");
	printf("=================================== \n");
	printf("|1 - VERIFICAR SE A LISTA ESTA VAZIA\n");
	printf("|2 - ISERIR UM NOME NA LISTA\n");
	printf("|3 - PESQUISA POR NOME\n");
	//printf("|4 - PESQUISA POR NUMERO\n");
	printf("|4 - LISTAR TODOS OS NOMES\n");
	printf("|5 - REMOVER UM NOME DA LISTA\n");
	printf("|99 - SAIR\n");

	scanf("%d", &opcao);
	return opcao;
}

int menu_remover_nome()
{
	int opcao = 0;

	printf("\n=================================== \n");
	printf("=     REMOVER UM NOME DA LISTA      =\n");
	printf("=================================== \n");
	printf("|1 - REMOVER PELO NOME\n");
	printf("|2 - REMOVER PELO NUMERO\n");

	scanf("%d", &opcao);
	return opcao;
}

t_elemento menu_pede_nome(t_elemento * dado)
{
	int opcao = 0;

	printf("\n=================================== \n");
	printf("=        REMOCAO POR NOME         =\n");
	printf("=================================== \n");
	printf("|DIGITE O NOME: ");
	scanf("%s", &dado->nome);
}

int menu_pede_numero()
{
	int opcao = 0;

	printf("\n=================================== \n");
	printf("=        REMOCAO POR NUMERO        =\n");
	printf("=================================== \n");
	printf("|DIGITE O NUMERO: ");
	scanf("%d", &opcao);

	return opcao;
}

void menu_tamanho_lista(t_no * lista)
{
	printf("\n=================================== \n");
	printf("=          TAMANHO DA LISTA       =\n");
	printf("=================================== \n");
	printf("|A LISTA ATUAL CONTEM %d ITENS \n\n", get_tamanho_encad(lista));
}

int remove_no(int opcao, t_no * lista)
{
	int posicao = 0;
	t_elemento dado; //Recebe o nome que se deseja procurar

	switch(opcao)
	{	
		case 1: menu_pede_nome(&dado);
				posicao = get_posicao_encad(lista, dado);//Busca por nome
				return posicao;//Retorna a posição + 1 para se adequar a função que vem em seguida

		case 2: posicao = menu_pede_numero(); //Busca por numero
				return posicao - 1;

		default: printf("Opcao Inválida");
	}
}

int menu_lista_nomes(t_no * lista)
{
	int tamanho = 0, i = 0;
	t_elemento * element_atual = NULL;

	tamanho = get_tamanho_encad(lista);
	
	if (tamanho <= 0)
	{
		menu_tamanho_lista(lista);
		return 0;
	}

	printf("\n=================================== \n");
	printf("=      LISTA NOMES NA LISTA       =\n");
	printf("=================================== \n");
	printf("|A LISTA ATUAL E COMPOSTA POR: \n");

	for(i = 0; i < tamanho; i++)
	{
		element_atual = get_elemento_encad(lista, i);
		printf("|%d - %s\n", i + 1, element_atual->nome);
	}
}

t_elemento menu_inserir_dados()
{
	t_elemento nome_user;

	printf("\n=================================== \n");
	printf("=        INSERIR NOVO NOME        =\n");
	printf("=================================== \n");
	printf("|DIGITE O NOME: ");
	scanf("%s", &nome_user.nome);

	return nome_user;
}

t_elemento menu_busca_nome()
{
	t_elemento nome_busca;

	printf("\n=================================== \n");
	printf("=      BUSCAR NOME NA LISTA        =\n");
	printf("=================================== \n");
	printf("|DIGITE O NOME: ");
	scanf("%s", &nome_busca.nome);

	return nome_busca;
}