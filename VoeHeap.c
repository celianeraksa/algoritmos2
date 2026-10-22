/*------------------------------------------------------------------------------------------------------------------------------------------------------------
Programa que implementa o Tipo Abstrato de Dados Heap em uma Fila de Prioridades, a ser utilizada pela empresa VoeHeap para auxiliar o embarque de seus voos
Objetivo: implementar e demonstrar na prática o uso do tipo abstrato Heap
Restricoes: o programa assume que nenhum nome de passageiro terá mais de 50 caracteres
  
Autores: Celiane Raksa (GRR20260578) e Maelly Tayna Machado (GRR20266234)
Disciplina: Algoritmos e Estrutura de Dados II
Data da última atualização: 20/10/2026
------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10	
#define TAM 1024

int j, aux; 

enum opcoes {adicionar=1, embarcar, restantes, heapsort, imprimir, inicheap, heapy, checar, gerar, sair}

//struct com nome e prioridade de cada passageiro
typedef struct {
	char* nome[50];
	int prioridade;
} passageiro;


// inicia o Heap com tamanho 0
void InicHeap( passageiro* vetor[], int* N){
	N = 0
	return;
}

void ChecaHeap(passageiro* vetor[], int N){
	for(int i = N, i > 1, i--){
		if (vetor[i] < vetor[i/2])
			return 1;
		else
			return 0;
	};
}

// troca dois valores usando uma variavel aux, vai ser usado na implementacao do Sacodeheap, HeapSort, RemoveHeap, etc
void Troca (passageiro vetor[], int N) {
	passageiro aux = v[a];
	v[a] = v[b];
	v[b] = v[a];
	
	return;
}

void SacodeHeap (passageiro vetor[], int N) {
	int i = 2;
	while (i <= N) {
		if (i < N && v[i].prioridade < v[i+1].prioridade)
			i++;
		if (v[i/2].prioridade >= v[i].prioridade)
			break;
		Troca(v, i/2, i);
		i = i *2;
	}
	return;
}

// imprime o menu para o usuario escolher a proxima opcao
void ImprimeMenu(){
	printf("****************************************");
	printf("[1] Adicionar os passageiros");
	printf("[2] Embarcar um passageiro");
	printf("[3] Ver passageiros restantes");
	printf("[4] Fazer o HeapSort");
	printf("[5] Imprimir");
	printf("[6] Iniciar Heap");
	printf("[7] Fazer Heapy");
	printf("[8] Checar se é heap");
	printf("[9] Gerar vetor e comparar QuickSort, InsertSort e HeapSort"); 
	printf("[10] Sair");
	printf("****************************************");
	
	return;
}

//insere 
void InsereHeap(passageiro* vetor[], int* N, passageiro novo){
	int i = N + 1;
	vetor[i] = novo;
	while (i > 1 && vetor[i/2].prioridade < vetor[i].prioridade){
		Troca(vetor, i, i/2);
		i = i/2;
	};
	
	*N = *N + 1;
	return;
}

void Heapfy(passageiro* vetor[], int N){
	int i;
	for (i = 1, i < N, i++)
		InsereHeap(vetor, i, vetor[i + 1]);
	return;
}
//imprime o vetor com os passageiros
void ImprimeHeap(passageiro*, int N) {
	for (int i = 1; i <= N; i++)
		printf("%s (%d)\n", v[i].nome, v[i].prioridade)
	return;
}

// ordena o vetor
void HeapSort(passageiro*, int N) {	//imprimir comparações e trocas
	//insere elementos no Heap
	Heapfy(vetor, N);
	//remove os elementos do Heap
	Troca(vetor, 1, N);
	N = N - 1;
	SacodeHeap(vetor, N);
	
	return;
}

// remove passageiro
passageiro RemoveHeap(passageiro*, int *N);
	passageiro removido = v[1];
	Troca(vetor, 1, *N);
	*N = *N - 1;
	SacodeHeap(vetor, *N);
	return removido;
}

	
// escolhe o pivo do quicksort usando o metodo mediana de tres
int EscolhePivo(int vetor[], int esq, int dir){
	
	int meio = (esq + dir)/2;
	
	if (vetor[esq] < vetor[dir]){ 
		if (vetor[esq] > vetor[meio]  
			return vetor[esq];
	}
	else if(vetor[esq] > vetor[dir]){
		if vetor[esq] < vetor[meio]
			return vetor[esq];
	}	
	else if (vetor[dir] < vetor[esq]){ 
		if (vetor[dir] > vetor[meio]) 
			return vetor[dir];
	}
	else if (vetor[dir] > vetor[esq]){
		if (vetor[dir] < vetor[meio])
			return vetor[dir];
	}
	else if (vetor[meio] < vetor[esq]){ 
		if (vetor[meio] > vetor[dir]) 
			return vetor[meio];
	}
	else if (vetor[meio] > vetor[esq]){
		if (vetor[meio] < vetor[dir])
			return vetor[meio];
	}
}
	
// faz as particoes nos (sub)vetores do quicksort
void particao(int vetor[], int esq, int dir, int *pos_pivo){

	int i, j, pivo, aux;
	pivo = EscolhePivo(vetor, esq, dir);

	i = esq; j = dir;
	
	while(i < j){
		while((vetor[i] <= pivo) && (i < dir)) i++;
			while (vetor[j] > pivo) j--;
			if (i < j){
				aux = vetor[j];
				vetor[j] = vetor[i];
				vetor[i] = aux;
			}
			vetor[esq] = vetor[j];
			vetor[j] = pivo;
			*pos_pivo = j;
	}
}

void QuickSort(int vetor[], int esq, int dir){	//imprimir compaações e trocas
	int pos_pivo;
	if (esq < dir){
		particao(vetor, esq, dir, &pos_pivo);
		QuickSort(vetor, esq, pos_pivo - 1);
		QuickSort(vetor, pos_pivo + 1, dir);
	};
}

void InsertSort(int vetor[], int N){	//imprimir comparações e trocas
	int aux, i, j;
	
	for (i =2, i <= N, i++){
		aux = vetor[i];
		j = i - 1;
		while (aux < vetor[j]){
			vetor[j + 1] = vetor[j];
			j--;
		};//while
		vetor[j + 1] = aux;
	};//for
}

void Embaralhar (int* vetor[], int N){
	if (N > 1){
		for (int i = N-1, i > 0, i--){
			int j = rand() % (i + 1);
			int aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
		};
	};
}

void GeraVetor (int* vetor[], int N){
	for (int i = 1, i <= N, i++)
		vetor[i] = (rand() % 1024);
}

int main(){

	srand(time(NULL));
		
	int livre[N];
	for (i = 1, i <= N, i++)
		livre[i] = i;

	Embaralhar(&livre, N);

	struct passageiro filaEmbarque[N];	

	InicHeap(filaEmbarque);	

	
	imprimeMenu();	
	scanf ("%d", &op);	//op é a escolha do usuario
	
	while (op != sair){
		if (op == adicionar){
			for(int i = 1, i < N, i++){
				scanf("%s", &filaEmbarque[i].nome); //****************************************************
				filaEmbarque[i].prioridade = livre[i];
			};//for			
		}//if
		else if (op == embarcar){
			printf("Quantos passageiros você deseja embarcar?");
			scanf("%d", nEmbarque);
			embarcar(filaEmbarque, nEmbarque);
		}
		else if (op == restantes)
			imprimir(filaEmbarque, N);	
		else if (op == heapsort){
			HeapSort(filaEmbarque, N);
			printf("O HeapSort foi realizado!");
		}
		else if (op == imprimir)
			imprimir(filaEmbarque, N);
		else if (op == inicheap){
			InicHeap(filaEmbarque);
			printf("Uma nova fila de embarque foi iniciada!");
		}
		else if (op == heapfy){
			Heapfy(filaEmbarque);
			printf("O vetor foi ordenado como um heap!");
		}
		else if (op == checar){
			int x = ChecaHeap(filaEmbarque);
			if (x == 1) printf ("É um heap");
			else printf ("Não é um heap");
		}
		else if (op == gerar){
			int* rdn[TAM] = GeraVetor(rdn, TAM);
			printf ("Um vetor com 1024 elementos aleatórios foi gerado");
			QuickSort(rdn, TAM);	//imprmir em cada função o numero de comparações e trocas
			InsertSort(rdn, TAM);	//passar os vetores sem ponteiros pra poder reutilizar
			HeapSort(rdn, TAM);
		}
		imprimeMenu();
	};//while  
	
	return 0;
}
