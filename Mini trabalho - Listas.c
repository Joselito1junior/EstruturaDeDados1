/*
	Falta implementar a inserção de disciplinas que trata-se de uma lista encadeada
	Falta o coódigo também tem muitas funções que não são usadas no primeiro momento, mas que foram criadas para futuras implementações
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 60

typedef struct elementos{
	char name_disciplina[50];		//Armazena o nome da disciplina que será armazenada
	float nota;							//Armazena a nota do aluno na disciplina em questão
}t_elemento; 

typedef struct Disciplina{
	t_elemento dado;				//Estrutura que armazena o nome da di
	struct Disciplina* prox;
}t_disciplina; //t_no

typedef struct Aluno{
	int matricula;
	t_disciplina* endereco;	
}t_aluno;

typedef struct Lista_alunos{
	t_aluno qtd_alunos[MAX];
	int n;
}t_lista_alunos;

///////////////////////////////////////////////
//Conjunto de funções para listas encadeadas///
///////////////////////////////////////////////

int chai_create_list();//Cria um novo no na lista encadeada
int chai_see_void_list();//Verifica se a lista está vazia
int chai_see_full_list();//Verifica se a lista está cheia
int chai_get_size_list();//Verifica o tamanho atual da lista
int chai_get_data_position();//Retorna os dados contidos na posiçao passada pelo usuário
int chai_get_position_data();//Retorna a posição do dado infomrado pelo usuário
int chai_move_right();//Movimenta todos os elementos para a direita
int chai_move_left();//Movimenta todos os elementos para a esquerda
int chai_insert_data_position();//Insere um novo elemnto na posição passada pelo usuário
int chai_remove_data_position();//Remove o elemento da posição indicada pelo usuário


///////////////////////////////////////////////
//Conjunto de funções para listas sequenciais//
///////////////////////////////////////////////
int seq_see_void_list(t_lista_alunos * P3CC);//Verifica se a lista está vazia
int seq_see_full_list(t_lista_alunos * P3CC);//Verifica se a lista está cheia
int seq_get_actual_size_list(t_lista_alunos * P3CC);//Verifica o tamanho atual da lista
t_aluno * seq_get_data_position(t_lista_alunos * P3CC, int pos);//Retorna os dados contidos na posiçao passada pelo usuário
int compara(t_aluno dado1, int dado2);//Retorna os dados enviados pela função seq_data_position
int seq_get_position_data(t_lista_alunos * P3CC, int dado);//Retorna a posição do dado infomrado pelo usuário
int seq_move_right(t_lista_alunos * P3CC, int pos);//Movimenta todos os elementos para a direita
int seq_move_left(t_lista_alunos * P3CC, int pos);	//Movimenta todos os elementos para a esquerda
int seq_insert_data_position(t_lista_alunos * P3CC, int pos, int dado);//Insere um novo elemnto na posição passada pelo usuário
int seq_remove_data_position(t_lista_alunos * P3CC, int pos);//Remove o elemento da posição indicada pelo usuário


///////////////////////////////////////////////
/////////////Funções de Manipulação////////////
///////////////////////////////////////////////
t_lista_alunos create_group();
int msg_opcao_invalida();
int apresentacao_inicial();
int menu_geral();
int insert_disciplinas(char nome[100], float nota);
int menu_usa_aluno(t_lista_alunos * P3CC);
int menu_usa_disciplina();
int menu_usa_nota();
int insert_nota();
int show_historic(t_lista_alunos * P3CC);

///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////FUNÇÃO PRINCIPAL//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
int main()
{
	t_lista_alunos P3CC;
	int opcao = -1; //Variável que armazena a opção do usuário após a chamada da função menu_principal
	
	//Inicializa a estrutura
	P3CC = create_group();
	
	//Chama apresentacao_inicial()
	apresentacao_inicial();
	
	//Chama menu_geral()
	do
	{
		int retorno = 0;
		opcao = menu_geral();
		
		//Realiza uma das operaçoes abaixo dependendo do valor retornado pela função acima
			//Opção 1 - chama a função menu_usa_aluno()				
			//Opção 2 - chama a função menu_usa_disciplina()
			//Opção 3 - chama a função menu_usa_nota()
			//Opção 4 - chama a função exibir_histórico()
			//Opção 0 - Sair
			//Opcao desconhecida - chama a função que indica que a opção é inválida
			
		switch(opcao)
		{
			case 0: break;
			case 1: retorno = menu_usa_aluno(&P3CC);
					if(!retorno) break;
			case 2: menu_usa_disciplina();
					break;
			case 3: menu_usa_nota();
					break;
			case 4: show_historic(&P3CC);
					break;
			default: msg_opcao_invalida();
		}
	}while(opcao);
	printf("\nVoce Saiu");
}

///////////////////////////////////////////////
//Conjunto de funções para listas sequenciais//
///////////////////////////////////////////////

//Verifica se a lista está vazia
int seq_see_void_list(t_lista_alunos * P3CC)
{
	return(P3CC->n == -1);
}

//Verifica se a lista está cheia
int seq_see_full_list(t_lista_alunos * P3CC)
{
	return(P3CC->n == MAX -1);
}

//Verifica o tamanho atual da lista
int seq_get_actual_size_list(t_lista_alunos * P3CC)
{
	return P3CC->n + 1;
}

//Retorna os dados contidos na posiçao passada pelo usuário
t_aluno * seq_get_data_position(t_lista_alunos * P3CC, int pos)
{
	if((pos > P3CC->n) || (pos < 0))
		return 0;
	return &(P3CC->qtd_alunos[pos]);
}

//Retorna os dados enviados pela função seq_data_position
int compara(t_aluno dado1, int dado2) {
    return (dado1.matricula == dado2);
}

//Retorna a posição do dado infomrado pelo usuário
int seq_get_position_data(t_lista_alunos * P3CC, int dado)
{
	int i;
	for(i = 0; i <= P3CC->n; i++)
		if(compara(P3CC->qtd_alunos[i], dado)==1)
			return i;
}

//Movimenta todos os elementos para a direita
int seq_move_right(t_lista_alunos * P3CC, int pos)
{
	int i;
	for(i = P3CC->n + 1; i > pos; i--)
		P3CC->qtd_alunos[i] = P3CC->qtd_alunos[i - 1];
	return 1;	
}

//Movimenta todos os elementos para a esquerda
int seq_move_left(t_lista_alunos * P3CC, int pos)
{
	int i;
	
	for (i = pos; i < (P3CC->n); i++)
		P3CC->qtd_alunos[i] = P3CC->qtd_alunos[i+1];
	return 1;
}	

//Insere um novo elemnto na posição passada pelo usuário
//Caso seja passado o valor -1 indica que o novo valor deve ser inserido na ultima posição disponível
int seq_insert_data_position(t_lista_alunos * P3CC, int pos, int dado)
{ 
	if(seq_see_full_list(P3CC) || (pos > P3CC->n + 1) || pos < 0)
		return 0;
	
	seq_move_right(P3CC, pos);
	P3CC->qtd_alunos[pos].matricula = dado;
	P3CC->qtd_alunos[pos].endereco = NULL;
	(P3CC->n)++;
	
	return 1;
}

//Remove o elemento da posição indicada pelo usuário
int seq_remove_data_position(t_lista_alunos * P3CC, int pos)
{
	if((pos > P3CC->n) || (pos < 0))
		return 0;
	
	seq_move_left(P3CC, pos);
	(P3CC->n)--;
	
	return 1;
}

///////////////////////////////////////////////
/////////////Funções de Manipulação////////////
///////////////////////////////////////////////
t_lista_alunos create_group()
{
	t_lista_alunos P3CC; //Variável que armazena a estrutura que guarda as informações da classe completa
	
	P3CC.n = -1;
	return P3CC;
}

int msg_opcao_invalida()
{
	printf("------------------------------------------\n");
	printf("[Desculpe, essa opcao nao e valida!]\n");
	printf("------------------------------------------\n\n");
}

int apresentacao_inicial()
{
	printf("\n------------------------------------\n");
	printf("\nAluno: Joselito Ferreira Melo Junior\n");
	printf("Disciplina: Estrutura de Dados 1\n");
	printf("Professor: Wallace Bonfim\n\n");
	printf("\n------------------------------------\n");
}

int menu_geral()
{
	//Cria variável opção
	int opcao = -1;
	
	//Exibe opções
		//Opção 1 - Editar Aluno
		//Opção 2 - Editar Disciplina
		//Opção 3 - Editar Nota
		//Opção 4 - Exibir Histórico
		//Opção 0 - Sair
		//Retorna opção esolhida
	printf("\n\n[HISTORICO ESCOLAR]\n");
	printf("1 - Editar Aluno\n");
	printf("2 - Editar Disciplina\n");
	printf("3 - Editar Nota\n");
	printf("4 - Exibir Historico\n");
	printf("0 - Sair\n");
	
	printf("Digite o numero da operacao que deseja realizar: ");
	scanf("%d", &opcao);
	return opcao;
}

int insert_disciplinas(char nome[100], float nota)
{
	//Verifica se já ha disciplinas para a matricula em questão
	//Verifica qual posição deve incluir 
	//Pede o nome da disciplina que deve ser incluida
	//Pede a nota que deve ser anexada a ela
	//Pesquisa se a disciplina ja existe no curriculo do aluno
		//Se não 
			//Cria um novo elo na lista encadeada
			//inclue o nome
			//chama a função insert_nota
		//Se sim 
			//indica que já existe
	//Verfica se deseja incluir outra
	//Se sim volta para o inicio
	//Se não retorna
	return 0;
}

int menu_usa_aluno(t_lista_alunos * P3CC)
{
	//Exibe opções
	//Opção 1 - Inserir Aluno Novo
				//inserir_aluno() 
				//menu_usa_disciplina()
				//Se o retorno da função for 0 indica que deve sair
				//Se o retorno da função for 1 indica que deve ser chamada a função de inserir_disciplina()
				//Se o retorno da função for 2 imprime que o aluno em questão não tem disciplina cadastrada
				
	//Opção 2 - Editar Aluno Veterano (Proxima Implementação)
				//edita_aluno()
				
	//Opção 0 - Voltar
				//Retorna 0
				
	int opcao = -1;
	int retorno = 0;
	int matricula = 0;
	int posicao = 0;
			
	do{	
		printf("\n\n[EDITAR ALUNO]\n");	
		printf("1 - Inserir Aluno Novo\n");
		printf("2 - Editar Aluno Veterano\n");
		printf("0 - Voltar\n");	
		printf("Escolha uma opcao: ");			
		scanf("%d", &opcao);
		
		switch(opcao)
		{			
			case 1: printf("\nDigite a matricula: ");
					scanf("%d", &matricula);
					printf("Digite a posicao: ");
					scanf("%d", &posicao);
					
					seq_insert_data_position(P3CC, posicao, matricula);
					do{
						printf("\nDeseja inserir disciplinas?\n");
						printf("1 - SIM\n");
						printf("0 - NAO\n");
						printf("Opcao: ");
						scanf("%d", &retorno);
					}while(retorno < 0 || retorno > 1);
					break;
					
			case 2:	printf("------------------------------------------\n");
					printf("Funcionalidade nao implementada!\n");
					printf("------------------------------------------\n\n");
					break;
		}
		return retorno;
	}while(opcao);
}
		
int menu_usa_disciplina()
{
	float nota = 0;
	char nome[100];
	//Exibe opções
	//Opção 1 - Inserir nova disciplina
				//Chama a função insert_disciplinas
				
	//Opção 2 - Editar disciplina (Proxima Implementação)
	//Opção 0 - Voltar
	//Retorna opção esolhida
	
	int opcao = -1;
	int retorno = 0;
			
	do{	
		printf("\n\n[EDITAR DISCIPLINA]\n");	
		printf("1 - Inserir Disciplina\n");
		printf("2 - Editar Disciplina\n");
		printf("0 - Voltar\n");	
		printf("Escolha uma opcao: ");			
		scanf("%d", &opcao);
		
		switch(opcao)
		{			
			case 1: printf("Digite o nome da disciplina: ");
					scanf("%s", &nome);
					printf("Digite a nota: ");
					scanf("%d", &nota);
					insert_disciplinas(nome, nota);
					break;
			case 2:	printf("------------------------------------------\n");
					printf("Funcionalidade nao implementada!\n");
					printf("------------------------------------------\n\n");
					break;
		}
		//return retorno;
	}while(opcao);
		
	return opcao;
}
		
int menu_usa_nota()
{
	//Exibe opções
	//Opção 1 - Inserir nova nota
	//Opção 2 - Editar nota (Proxima Implementação)
	//Opção 0 - Voltar
	//Retorna opção esolhida
}
	
int insert_nota()
{
	//Imprime que qualquer outra nota associada àquela disciplina será apagada e espera confirmação
		//se sim reescreve a nota
		//Se não volta e indica que a nota atual não foi alterada
}	
int show_historic(t_lista_alunos * P3CC)
{
	//exibe através do número da matricula todas as disciplinas com suas respectivas notas para o aluno em questão
	
	int i = 0;
	
	for(i = 0; i <= P3CC->n; i++)
		printf("Aluno %d matricula: %d\n", i, P3CC->qtd_alunos[i].matricula);
}