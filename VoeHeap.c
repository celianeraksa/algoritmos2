//Celiane Raksa - GRR20260578
//Maelly ***** - GRR2026****
//Função principal do VoeHeap

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

struct passageiro{
	char* nome[50];
	int prioridade;
};

void InicHeap(struct passageiro*);

void ImprimeMenu(){

void Heapfy(struct passageiro*, int);

void ImprimeHeap(struct passageiro*, int);

void HeapSort(struct passageiro*, int N);

void RemoveHeap(struct passageiro*);

void QuickSort(struct passageiro*, int);

void InsertSort(struct passageiro*, int);


int main(){

	srand(time(NULL));

	struct passageiro filaEmbarque[N];	//fazer struct passageiro

	InicHeap(filaEmbarque);	//implementar função

	//colocar menu com adicionar passageiros, embarcar, imprimir fila, heapSort, imprimir vetor ordenado(dps do sort), sair
	//dá pra fazer um enum com cada opção do menu

	imprimeMenu();	//implementar função
	scanf ("%d", &op);	//op é a escolha do usuario
	
	while (op != sair){
		if (op == adicionar){
			for(int i = 1, i < N, i++){
				filaEmbarque[i].nome = //ler nome
				filaEmbarque[i].prioridade = 1 + (rand()%N);
			};//for
			Heapfy(filaEmbarque, N);	//implementar função
		}//if
		
		else if (op == imprime)
			ImprimeHeap(filaEmbarque);
	
		else if (op == heapsort){
			HeapSort(filaEmbarque);	//implementar função
			ImprimeHeap(filaEmbarque);	//dá pra usar a mesma?
		};//else if
	
		imprimeMenu();
		
		embarcar(filaEmbarque)	//percorrer o heap e usar o RemoveHeap(), imprimindo a cada loop qual foi o passageiro embarcado (nome + prioridade)

	};//while  
	
	return 0;
}
