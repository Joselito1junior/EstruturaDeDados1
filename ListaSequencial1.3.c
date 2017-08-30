/**
 *	author: Joselito Ferreira Melo Junior
 *  Nessa versão 1.3 foi implementada a "Remoção" na lista através da função remover()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 #define	MAX 10

/////////////////////////////////////////////////////////////
//Estruturas 
// Tipo base dos elementos da lista
typedef struct elementos {
    char nome[50];
    // Outros elementos
} t_elemento;

// Estrutura da lista
typedef struct lista {
    t_elemento vetor[MAX];//vet que armazena elem. da pilha
    int n; // posicao (indice) da ultima posição ocupada na lista
} t_lista; // tipo lista

/////////////////////////////////////////////////////////////
//Funções
t_lista criar();
int inserir (t_lista * lista, int pos, t_elemento dado);
int isCheia(t_lista * lista);
int deslocaDireita(t_lista * lista, int pos);
t_elemento * getElemento(t_lista * lista, int pos);
int remover (t_lista *lista, int pos);
int deslocaEsquerda(t_lista * lista, int pos);

 
/////////////////////////////////////////////////////////////
//Loop
int main()
{
	t_lista mylista;
	char nome_aux[256];
	int i = 0, qtd_nomes = 0;
	t_elemento ele_aux;
	t_elemento *list_position_data;
	int search = 0;
	int removido = -1;
	int remover_posi = 0;
	int opcao = 0;
	
	//Criar lista	
	mylista = criar();
	
	printf("Digite quantos nomes serao guardados: ");
	scanf("%d", &qtd_nomes);
	
	//Guarda varios nomes
	for(i = 0; i < qtd_nomes; i++)
	{
		//Solicitar nomes
		printf("Digite um nome para a %d posicao: ", i + 1);
		scanf("%s", &ele_aux.nome);//Recebe um nome
		//Armazenar na lista
		inserir(&mylista, i, ele_aux);
	}
	printf("\n");
		
	//mostrar nomes
	//loop
	//for(i = 0; i <= mylista.n; i++)printf("O nome do %d elemento e: [%s]\n", i + 1, mylista.vetor[i].nome);//print do valor de cada iteração			

	//Inclusão da versão 1.2
	printf("Digite o numero da posicao para que seja exibido seu valor: ");
	scanf("%d", &search);
	
	list_position_data = getElemento(&mylista, search - 1);//Decrementa o valor digitado pelo usuário para igualar ao valor do indice do vetor.
	printf("O valor armazenado na posicao %d e [%s]: \n",search, list_position_data);
	
	
	//Inclusão da versão 1.3
	printf("Digite a posicao para que seu valor seja removido: ");
	scanf("%d", &remover_posi);
	
	removido = remover(&mylista, remover_posi - 1);
	if(removido) printf("O item [%d] foi removido\n", remover_posi);
	else printf("O item [%d] não pode ser removido\n");
	
	printf("Deseja ver os nomes restantes? \n");
	printf("[1]Sim \n");
	printf("[0]Nao \n");
	scanf("%d", &opcao);
	
	if(opcao)
		for(i = 0; i <= mylista.n; i++)printf("O nome do %d elemento e: [%s]\n", i + 1, mylista.vetor[i].nome);//print do valor de cada iteração			
	else
		printf("Saindo");
}

/**
 * Cria uma nova lista, inicializa o n, e retorna o registro.
 * 
 * @return Lista inicializada
 */
t_lista criar() {
	
    t_lista lista;//
	
    lista.n = -1;
    return lista;
}

/**
 * Insere um elemento (dado) em determinada posicao da lista.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 * @param pos   posicao do elemento, a partir do qual sera iniciado o deslocamento.
 * @param dado  elemento a ser inserido
 *
 * @return Falso(0) se a posição for invalida ou se a lista estiver cheia, caso contrario, retorna Verdadeiro(1).
 */
int inserir (t_lista * lista, int pos, t_elemento dado) {
    if ( isCheia(lista) || (pos > lista->n + 1) || (pos < 0) )
        return 0;

    deslocaDireita(lista, pos);
    lista->vetor[pos] = dado;
    (lista->n)++;
    return 1;
}

/**
 * Verifica se a lista esta cheia ou nao.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 *
 * @return Verdadeiro (1) se a lista estiver cheia, ou falso (0) caso contrario.
 */
int isCheia(t_lista * lista) {
    return (lista->n == MAX-1);
}

/**
 * Desloca os elementos da lista para a direita a partir de pos
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 * @param pos   posicao do elemento, a partir do qual sera iniciado o deslocamento.
 *
 * @return Falso(0) se a posição for invalida ou se a lista estiver cheia, caso contrario, retorna Verdadeiro(1).
 */
int deslocaDireita(t_lista * lista, int pos) {
    int i;

    for (i=lista->n + 1; i>pos; i--)
        lista->vetor[i] = lista->vetor[i-1];

    return 1;
}

/**
 * Obtem um elemento da lista especificado por pos.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 * @param pos   posicao do elemento desejado
 *
 * @return ponteiro para o elemento desejado, caso a posicao seja invalida retorna 0.
 */
t_elemento * getElemento(t_lista * lista, int pos) {
    // verifica se pos eh valida
    if ( (pos > lista->n) || (pos < 0) )
        return 0;
    return &(lista->vetor[pos]);
}

/**
 * Remove um elemento de determinada posicao da lista.
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 * @param pos   posicao do elemento, a partir do qual sera iniciado o deslocamento.
 *
 * @return Falso(0) se a posição for invalida ou se a lista estiver cheia, caso contrario, retorna Verdadeiro(1).
 */
int remover (t_lista *lista, int pos) {
    if ( (pos > lista->n) || (pos < 0) )
        return 0;

    deslocaEsquerda(lista, pos);
    (lista->n)--;
    return 1;
}

/**
 * Desloca os elementos da lista para a esquerda a partir de pos
 * 
 * @param lista ponteiro para a lista, a lista ja deve ter sido inicializada
 * @param pos   posicao do elemento, a partir do qual sera iniciado o deslocamento.
 *
 * @return 0 se a posição for invalida ou se a lista estiver cheia, caso contrario, retorna 1.
 */
int deslocaEsquerda(t_lista * lista, int pos) {
    int i;

    for (i=pos; i<(lista->n); i++)
        lista->vetor[i] = lista->vetor[i+1];

    return 1;
}