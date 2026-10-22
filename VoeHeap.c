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
int* nEmbarque = 0; 

enum opcoes {adicionar=1, embarcar, restantes, heapsort, imprimir, inicheap, heapy, checar, gerar, sair}

//struct com nome e prioridade de cada passageiro
typedef struct {
	char nome[50];
	int prioridade;
} passageiro;


// inicia o Heap com tamanho 0
void InicHeap( passageiro* vetor[], int* N){
	*N = 0
	return;
}

void ChecaHeap(passageiro* vetor[], int N){
	for(int i = N; i > 1; i--){
		if (vetor[i] < vetor[i/2])
			return 1;
		else
			return 0;
	};
}

// troca dois valores usando uma variavel aux, vai ser usado na implementacao do Sacodeheap, HeapSort, RemoveHeap, etc
void Troca (passageiro vetor[], int N) {
	passageiro aux = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = aux;
	
	return;
}

void SacodeHeap (passageiro* vetor[], int N) {
	int i = 2;
	while (i <= N) {
		if (i < N && vetor[i].prioridade < vetor[i+1].prioridade)
			i++;
		if (vetor[i/2].prioridade >= vetor[i].prioridade)
			break;
		Troca(vetor, i/2, i);
		i = i *2;
	};
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
	for (i = 1; i < N; i++)
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
passageiro RemoveHeap(passageiro* vetor, int *N);
	passageiro removido = vetor[1];
	Troca(vetor, 1, *N);
	*N = *N - 1;
	SacodeHeap(vetor, *N);
	return removido;
}

	
// devolve a POSICAO da mediana entre vetor[esq], vetor[meio]
int EscolhePivo(int vetor[], int esq, int dir){
	int meio = (esq + dir)/2;
	int a = vetor[esq], b = vetor[meio], c = vetor[dir];

	comparacoes++;
	
	if (a < b){ 
		comparacoes++;
		if (b < c)  
			return meio; //a < b < c
		comparacoes++;
		if (a < c)
			return dir; // a < c <= b
		return esq; // c <=a < b
	}
	else {
		comparacoes++;
		if (a < c) 
			return esq; // b <= a < c
		comparacoes++;
		if (b < c)
			return dir; // b < c <= a
		return meio; // c <= b <= a
	}
}
	
// faz as particoes nos (sub)vetores do quicksort
void particao(int vetor[], int esq, int dir, int *pos_pivo){

	int i, j, pivo, aux, p;
	p = EscolhePivo(vetor, esq, dir);
	if ( p != esq){ // leva a mediana para esq
		aux = vetor[p];
		vetor[p] = vetor[esq];
		vetpr[esq] = aux;
		trocas++;
	}
	pivo = vetor[esq];

	i = esq; j = dir;
	
	while(i < j){
		// i anda para a direita enquanto vetor[i] <= pivo
		while (i < dir && vetor[i] <= pivo) {
			comparacoes++; // comparacao que deu verdadeiro
			i++;
		}
		if (i < dir)
			comparacoes++; // a que falhou (vetor[i] > pivo)
		// j anda para a esquerda enquanto vetor[j] > pivo
		while (vetor[j] > pivo){
			comparacoes++; // comparaco que deu verdadeiro
			j--;
		}
		comparacoes++; // a que falhou (vetor[j] <= pivo)
		if (i < j){
			aux = vetor[j];
			vetor[j] = vetor[i];
			vetor[i] = aux;
			trocas++;
			}
	}
			// armazena o pivo (que esta em vetor[esq]) na poiscao j
	if (j != esq)
		trocas++;
		vetor[esq] = vetor[j];
		vetor[j] = pivo;
		*pos_pivo = j;
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
	for (int i = 1; i <= N; i++)
		vetor[i] = (rand() % 1024);
}

void embarcar (passageiro* vetor[], int* N){
	passageiro menor = vetor[1];
	for (int i = 1; i < N; i++){
		if (vetor[i].prioridade < menor.prioridade)
			menor = vetor[i];
	};
	printf ("%s foi embarcado/a! Sua posição na fila era $d\n", menor.nome, menor.prioridade);
	RemoveHeap(vetor[i], vetor, N);	//RemoveHeap já arruma o buraco?
}

int main(){

	srand(time(NULL));
		
	int livre[N];
	for (i = 1; i <= N; i++)
		livre[i] = i;

	Embaralhar(&livre, N);

	char dados[] = "dados.txt";
	FILE* arq = fopen(dados, "r");

	struct passageiro filaEmbarque[N];	

	InicHeap(filaEmbarque);	

	
	imprimeMenu();	
	scanf ("%d", &op);	//op é a escolha do usuario
	
	while (op != sair){
		if (op == adicionar){
			for(int i = 1, i < N, i++){
				if (arq == NULL){
					printf("Ocorreu um erro ao ler os dados!");
					return 0;
				};//if
				while ((fgets(filaEmbarque[i].nome, 50, arq)) != NULL);
				filaEmbarque[i].prioridade = livre[i];
			};//for			
		}//if
		else if (op == embarcar){
			printf("Quantos passageiros você deseja embarcar?");
			scanf("%d", &nEmbarque);
			for (aux = 0; aux < nEmbarque; aux++)
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

	fclose(arq);
	return 0;
}
