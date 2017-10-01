/*
	Falta implementar a inser��o de disciplinas que trata-se de uma lista encadeada
	Falta o co�digo tamb�m tem muitas fun��es que n�o s�o usadas no primeiro momento, mas que foram criadas para futuras implementa��es
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 60

typedef struct elementos{
	char name_disciplina[50];		//Armazena o nome da disciplina que ser� armazenada
	float nota;							//Armazena a nota do aluno na disciplina em quest�o
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
//Conjunto de fun��es para listas encadeadas///
///////////////////////////////////////////////

int chai_create_list();//Cria um novo no na lista encadeada
int chai_see_void_list();//Verifica se a lista est� vazia
int chai_see_full_list();//Verifica se a lista est� cheia
int chai_get_size_list();//Verifica o tamanho atual da lista
int chai_get_data_position();//Retorna os dados contidos na posi�ao passada pelo usu�rio
int chai_get_position_data();//Retorna a posi��o do dado infomrado pelo usu�rio
int chai_move_right();//Movimenta todos os elementos para a direita
int chai_move_left();//Movimenta todos os elementos para a esquerda
int chai_insert_data_position();//Insere um novo elemnto na posi��o passada pelo usu�rio
int chai_remove_data_position();//Remove o elemento da posi��o indicada pelo usu�rio


///////////////////////////////////////////////
//Conjunto de fun��es para listas sequenciais//
///////////////////////////////////////////////
int seq_see_void_list(t_lista_alunos * P3CC);//Verifica se a lista est� vazia
int seq_see_full_list(t_lista_alunos * P3CC);//Verifica se a lista est� cheia
int seq_get_actual_size_list(t_lista_alunos * P3CC);//Verifica o tamanho atual da lista
t_aluno * seq_get_data_position(t_lista_alunos * P3CC, int pos);//Retorna os dados contidos na posi�ao passada pelo usu�rio
int compara(t_aluno dado1, int dado2);//Retorna os dados enviados pela fun��o seq_data_position
int seq_get_position_data(t_lista_alunos * P3CC, int dado);//Retorna a posi��o do dado infomrado pelo usu�rio
int seq_move_right(t_lista_alunos * P3CC, int pos);//Movimenta todos os elementos para a direita
int seq_move_left(t_lista_alunos * P3CC, int pos);	//Movimenta todos os elementos para a esquerda
int seq_insert_data_position(t_lista_alunos * P3CC, int pos, int dado);//Insere um novo elemnto na posi��o passada pelo usu�rio
int seq_remove_data_position(t_lista_alunos * P3CC, int pos);//Remove o elemento da posi��o indicada pelo usu�rio


///////////////////////////////////////////////
/////////////Fun��es de Manipula��o////////////
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
/////////////////////////////FUN��O PRINCIPAL//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
int main()
{
	t_lista_alunos P3CC;
	int opcao = -1; //Vari�vel que armazena a op��o do usu�rio ap�s a chamada da fun��o menu_principal
	
	//Inicializa a estrutura
	P3CC = create_group();
	
	//Chama apresentacao_inicial()
	apresentacao_inicial();
	
	//Chama menu_geral()
	do
	{
		int retorno = 0;
		opcao = menu_geral();
		
		//Realiza uma das opera�oes abaixo dependendo do valor retornado pela fun��o acima
			//Op��o 1 - chama a fun��o menu_usa_aluno()				
			//Op��o 2 - chama a fun��o menu_usa_disciplina()
			//Op��o 3 - chama a fun��o menu_usa_nota()
			//Op��o 4 - chama a fun��o exibir_hist�rico()
			//Op��o 0 - Sair
			//Opcao desconhecida - chama a fun��o que indica que a op��o � inv�lida
			
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
//Conjunto de fun��es para listas sequenciais//
///////////////////////////////////////////////

//Verifica se a lista est� vazia
int seq_see_void_list(t_lista_alunos * P3CC)
{
	return(P3CC->n == -1);
}

//Verifica se a lista est� cheia
int seq_see_full_list(t_lista_alunos * P3CC)
{
	return(P3CC->n == MAX -1);
}

//Verifica o tamanho atual da lista
int seq_get_actual_size_list(t_lista_alunos * P3CC)
{
	return P3CC->n + 1;
}

//Retorna os dados contidos na posi�ao passada pelo usu�rio
t_aluno * seq_get_data_position(t_lista_alunos * P3CC, int pos)
{
	if((pos > P3CC->n) || (pos < 0))
		return 0;
	return &(P3CC->qtd_alunos[pos]);
}

//Retorna os dados enviados pela fun��o seq_data_position
int compara(t_aluno dado1, int dado2) {
    return (dado1.matricula == dado2);
}

//Retorna a posi��o do dado infomrado pelo usu�rio
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

//Insere um novo elemnto na posi��o passada pelo usu�rio
//Caso seja passado o valor -1 indica que o novo valor deve ser inserido na ultima posi��o dispon�vel
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

//Remove o elemento da posi��o indicada pelo usu�rio
int seq_remove_data_position(t_lista_alunos * P3CC, int pos)
{
	if((pos > P3CC->n) || (pos < 0))
		return 0;
	
	seq_move_left(P3CC, pos);
	(P3CC->n)--;
	
	return 1;
}

///////////////////////////////////////////////
/////////////Fun��es de Manipula��o////////////
///////////////////////////////////////////////
t_lista_alunos create_group()
{
	t_lista_alunos P3CC; //Vari�vel que armazena a estrutura que guarda as informa��es da classe completa
	
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
	//Cria vari�vel op��o
	int opcao = -1;
	
	//Exibe op��es
		//Op��o 1 - Editar Aluno
		//Op��o 2 - Editar Disciplina
		//Op��o 3 - Editar Nota
		//Op��o 4 - Exibir Hist�rico
		//Op��o 0 - Sair
		//Retorna op��o esolhida
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
	//Verifica se j� ha disciplinas para a matricula em quest�o
	//Verifica qual posi��o deve incluir 
	//Pede o nome da disciplina que deve ser incluida
	//Pede a nota que deve ser anexada a ela
	//Pesquisa se a disciplina ja existe no curriculo do aluno
		//Se n�o 
			//Cria um novo elo na lista encadeada
			//inclue o nome
			//chama a fun��o insert_nota
		//Se sim 
			//indica que j� existe
	//Verfica se deseja incluir outra
	//Se sim volta para o inicio
	//Se n�o retorna
	return 0;
}

int menu_usa_aluno(t_lista_alunos * P3CC)
{
	//Exibe op��es
	//Op��o 1 - Inserir Aluno Novo
				//inserir_aluno() 
				//menu_usa_disciplina()
				//Se o retorno da fun��o for 0 indica que deve sair
				//Se o retorno da fun��o for 1 indica que deve ser chamada a fun��o de inserir_disciplina()
				//Se o retorno da fun��o for 2 imprime que o aluno em quest�o n�o tem disciplina cadastrada
				
	//Op��o 2 - Editar Aluno Veterano (Proxima Implementa��o)
				//edita_aluno()
				
	//Op��o 0 - Voltar
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
	//Exibe op��es
	//Op��o 1 - Inserir nova disciplina
				//Chama a fun��o insert_disciplinas
				
	//Op��o 2 - Editar disciplina (Proxima Implementa��o)
	//Op��o 0 - Voltar
	//Retorna op��o esolhida
	
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
	//Exibe op��es
	//Op��o 1 - Inserir nova nota
	//Op��o 2 - Editar nota (Proxima Implementa��o)
	//Op��o 0 - Voltar
	//Retorna op��o esolhida
}
	
int insert_nota()
{
	//Imprime que qualquer outra nota associada �quela disciplina ser� apagada e espera confirma��o
		//se sim reescreve a nota
		//Se n�o volta e indica que a nota atual n�o foi alterada
}	
int show_historic(t_lista_alunos * P3CC)
{
	//exibe atrav�s do n�mero da matricula todas as disciplinas com suas respectivas notas para o aluno em quest�o
	
	int i = 0;
	
	for(i = 0; i <= P3CC->n; i++)
		printf("Aluno %d matricula: %d\n", i, P3CC->qtd_alunos[i].matricula);
}