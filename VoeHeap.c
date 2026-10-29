/*------------------------------------------------------------------------------------------------------------------------------------------------------------
Programa que implementa o Tipo Abstrato de Dados Heap em uma Fila de Prioridades, a ser utilizada pela empresa VoeHeap para auxiliar o embarque de seus voos
Objetivo: implementar e demonstrar na prática o uso do tipo abstrato Heap
Restricoes: o programa assume que nenhum nome de passageiro terá mais de 50 caracteres
  
Autores: Celiane Raksa (GRR20260578) e Maelly Tayna Machado (GRR20266234)
Disciplina: Algoritmos e Estrutura de Dados II
Data da última atualização: 29/10/2026
------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// capacidade do aviao (constante)
#define CAPACIDADE 30 
// tamanho do vetor de teste para comparacoes entre algoritmos de ordenacao
#define TAM_VETOR 1024

long comparacoes = 0, trocas = 0; // contadores globais

enum opcoes {adicionar=1, embarque, restantes, heapsort, imprimir, inicheap, heapfy, checar, gerar, sair};

//struct com nome e prioridade de cada passageiro
typedef struct {
	char nome[50];
	int prioridade;
} passageiro;


// inicia o Heap com tamanho 0
void InicHeap(int* N){
	*N = 0;
	return;
}

int ChecaHeap(passageiro vetor[], int N){
	for(int i = N; i > 1; i--){
		if (vetor[i].prioridade > vetor[i/2].prioridade)
			return 0; // filho maior que o pai: nao eh heap
	}
	return 1; // nenhuma violacao: eh heap
}

// troca dois valores usando uma variavel aux, vai ser usado na implementacao do Sacodeheap, HeapSort, RemoveHeap, etc
void Troca (passageiro vetor[], int a, int b){
	passageiro aux = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = aux;
	trocas++;
	return;
}

void SacodeHeap (passageiro vetor[], int N){
	int i = 2; // filho esquerdo da raiz
	while (i <= N){
		if (i < N) { //existe filho direito?
			comparacoes++;
			if (vetor[i].prioridade < vetor[i+1].prioridade)
			i++; // i passa a ser o maior filho
		}
		comparacoes++;
		if (vetor[i/2].prioridade >= vetor[i].prioridade)
			break; // pai >= filho entao ja esta certo
		Troca(vetor, i/2, i); // pai desce, filho sobe
		i = i *2; // continua pelo filho esquerdo
	};
	return;
}

// imprime o menu para o usuario escolher a proxima opcao
void ImprimeMenu(){
	printf("****************************************\n");
	printf("[1] Adicionar os passageiros\n");
	printf("[2] Embarcar passageiros\n");
	printf("[3] Ver passageiros restantes\n");
	printf("[4] Fazer o HeapSort\n");
	printf("[5] Imprimir\n");
	printf("[6] Iniciar Heap\n");
	printf("[7] Fazer Heapfy\n");
	printf("[8] Checar se eh heap\n");
	printf("[9] Gerar vetor e comparar QuickSort, InsertSort e HeapSort\n"); 
	printf("[10] Sair\n");
	printf("****************************************\n");
	
	return;
}

//insere novo passageiro no final do vetor e reorganiza o Max-heap
void InsereHeap(passageiro vetor[], int* N, passageiro novo){
	int i = *N + 1;
	vetor[i] = novo;
	while (i > 1) {
		comparacoes++;
		if (vetor[i/2].prioridade < vetor[i].prioridade){
			Troca(vetor, i, i/2); // pai eh menor que o filho, entao sobe
			i = i/2;
		}
		else {
			break;
		}
	}
	*N = *N + 1;
}

void Heapfy(passageiro vetor[], int N){
	int tamanho = 1;
	for (int i = 1; i < N; i++)
		InsereHeap(vetor, &tamanho, vetor[i + 1]);
	return;
}
//imprime o vetor com os passageiros
void ImprimeHeap(passageiro vetor[], int N){
	if (N <= 0) {
		printf("O aviao esta vazio! Nao ha passageiros para exibir.\n");
		return;
	}
	printf("--- LISTA DE PASSAGEIROS---\n");
	for (int i = 1; i <= N; i++)
		printf("Nome: %s Posicao: %d Prioridade: %d\n", vetor[i].nome, i, vetor[i].prioridade);
	return;
}


void HeapSort(passageiro vetor[], int N){	//imprimir comparações e trocas
	Heapfy(vetor, N); // 1a parte: monta o heap
	while (N > 1) { // 2a parte: remove o maior varias vezes
		Troca(vetor, 1, N); // maior vai para a posicao final
		N = N - 1; // o fim sai do heap
		SacodeHeap(vetor, N); // conserta a raiz
	}
	return;
}

// remove e retorna o passageiro de maior prioridade
passageiro RemoveHeap(passageiro vetor[], int *N){
	passageiro removido = vetor[1]; // guarda o passageiro a ser removido
	Troca(vetor, 1, *N); // subtitui a raiz pelo ultimo elemento do heap
	*N = *N - 1; // decrementa o tamanho
	SacodeHeap(vetor, *N); // reorganiza o heap para que mantenha suas propriedades
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
	};
}
	
// faz as particoes nos (sub)vetores do quicksort
void particao(int vetor[], int esq, int dir, int *pos_pivo){

	int i, j, pivo, aux, p;
	p = EscolhePivo(vetor, esq, dir);
	if ( p != esq){ // leva a mediana para esq
		aux = vetor[p];
		vetor[p] = vetor[esq];
		vetor[esq] = aux;
		trocas++;
	}
	pivo = vetor[esq];

	i = esq; j = dir;
	
	while(i < j){
		// i anda para a direita enquanto vetor[i] <= pivo
		while (i < dir && vetor[i] <= pivo){
			comparacoes++; // comparacao que deu verdadeiro
			i++;
		};
		if (i < dir)
			comparacoes++; // a que falhou (vetor[i] > pivo)
		// j anda para a esquerda enquanto vetor[j] > pivo
		while (vetor[j] > pivo){
			comparacoes++; // comparaco que deu verdadeiro
			j--;
		};
		comparacoes++; // a que falhou (vetor[j] <= pivo)
		if (i < j){
			aux = vetor[j];
			vetor[j] = vetor[i];
			vetor[i] = aux;
			trocas++;
			};
	}
			// armazena o pivo (que esta em vetor[esq]) na poiscao j
	if (j != esq){
		trocas++;
	vetor[esq] = vetor[j];
	vetor[j] = pivo;
	*pos_pivo = j;
	};
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
	for (i = 2; i <= N; i++){
		aux = vetor[i];
		j = i - 1;
		while (j >= 1){
			comparacoes++;
			if (aux >= vetor[j])
				break; // ja esta no lugar
			vetor[j + 1] = vetor[j]; // desloca (conta como troca)
			trocas++;
			j--;
		}
		vetor[j + 1] = aux;
	}
}

void Embaralhar (int vetor[], int N){
	if (N > 1){
		for (int i = N; i > 1; i--){
			int j = rand() % i + 1; // sorteia entre 1 e i
			int aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
		};
	};
}

void GeraVetor (int vetor[], int N){
	for (int i = 1; i <= N; i++)
		vetor[i] = (rand() % 1024);
}

void embarcar (passageiro vetor[], int *N){
	//verifica se esta vazio
	if (*N == 0) {
		printf("\nNao ha passageiros na fila de embarque!\n");
		return;
	}
	// o removeheap ja tira o de maior prioridade do topo (raiz)
	passageiro p = RemoveHeap(vetor, N);
	printf("\nPassageiro embarcado: %s, Prioridade: %d\n", p.nome, p.prioridade);
}

void PreencheLivre(int vetor[], int N){
	for (int i = 1; i <= N; i++)
		vetor[i] = i;
	Embaralhar(vetor, N);
}
int main(){
	// o heap do aviao usa as posicoes 1..N (a posicao 0 nao eh usada)
	// o tamanho eh capacidade + 1 para caber todos os passageiros do aviao
	passageiro filaEmbarque[CAPACIDADE + 1];
	/* copia da fila, usada para ordenar (heapsort) ou demonstrar 
	o heapfy sem estragar o heap 
	*/
	passageiro copia[CAPACIDADE + 1];
	// passageiro auxiliar, guarda o que esta sendo inserido ou removido
	passageiro p;
	/* prioridades de 1 ate CAPACIDADE embaralhadas. assim cada
	passsageiro recebe uma e nao existem prioridades iguais (grupos de prioridade)
	*/
	int livre [CAPACIDADE + 1];
	int N; // quantos passageiros estao no heap AGORA (muda qnd insere/remove)
	int op; //opcao escolhida pelo usuario no menu
	int qtd; // quantos passageiros o usuario quer embarcar de uma vez
	int i; // contador usado nos lacos for
	FILE *arq; // arquivo com os nomes dos passageiros

	//inicia o gerador de numeros aleatorios
	srand(time(NULL));
	InicHeap(&N);	// comeca com o heap vazio (N=0)

	printf("Antes de tudo, lembre-se de iniciar seu heap ;)\n");
	
	//mostra o menu e le a primeira opcao
	ImprimeMenu();	
	scanf("%d", &op);	//op é a escolha do usuario
	// o laco repete ate o usuario escolher sair
	while (op != sair){
		//"adicionar" le os nomes do arquivo e monta o heap
		if (op == adicionar){
			//verifica se ja foram adicionados para evitar bugs
			if (N >= 10)
				printf("\nAviso: os passageiros ja foram adicionados!\n");
			else {
				arq =  fopen("dados.txt", "r");
				if (arq == NULL){ // sem o arquivo nao eh possivel ler os nomes
					printf("Ocorreu um erro ao ler os dados!");
					return 1; // termina o programa	
				}
				else{
					InicHeap(&N); // recomeca o aviao, heap vazio
					//preenche livre com 1 ate CAPACIDADE e embaralha
					PreencheLivre(livre, CAPACIDADE);
					int i = 1;
					// cada volta le um linha do arquivo (nome) e insere o passageiro checando a capacidade
					while (i <= CAPACIDADE && fgets(p.nome, sizeof(p.nome), arq) != NULL) {
						// troca o "\n" da quebra de linha por "\0"
                    	p.nome[strcspn(p.nome, "\r\n")] = '\0';
                    	p.prioridade = livre[i];
						// InsereHeap coloca o passageiro no lugar certo do heap e aumenta o N sozinho
                    	InsereHeap(filaEmbarque, &N, p); 
						i++;
                	}
               		fclose(arq);
                	printf("%d passageiros adicionados.\n", N);
            	}
			}
		}
		// "embarcar" remove os passageiros de maior prioridade
        else if (op == embarque){
            if (N <= 0){
                printf("Ninguem a embarcar.\n");
            } 
			else{
				int qtd;
                printf("Quantos passageiros embarcar?\n ");
                scanf("%d", &qtd);
				/* nao da para embarcar mais gente do que tem no heap
				nem uma quantidade negativa*/
                if (qtd > N) {
					printf("Aviso: solicitado embarque de %d, mas so existem %d passageiros. Ajustando...\n", qtd, N);
					qtd = N;
				}
				if (qtd < 0) qtd = 0;
                for (int j = 0; j < qtd; j++){
                    embarcar(filaEmbarque, &N);
                };
            };
        }
			// "restantes" mostra quem ainda nao embarcou
        else if (op == restantes){
            printf("Restam: %d passageiros.\n", N);
            ImprimeHeap(filaEmbarque, N);
        }
		// "heapsort" ordena uma COPIA e mostra comparacoes e trocas
        else if (op == heapsort){
            if (N == 0){
                printf("Heap vazio.\n");
            } 
			else{
				/* o heapsort desmancha o heap de prioridades, por isso ordenamos
				uma copia e a fila do aviao continua valida para os prox embarques */
                for (i = 1; i <= N; i++) 
					copia[i] = filaEmbarque[i];
                comparacoes = 0; trocas = 0; // zera os contadores antes de ordenar
                HeapSort(copia, N);
                printf("Vetor ordenado (crescente):\n");
                ImprimeHeap(copia, N);
                printf("HeapSort: %ld comparacoes, %ld trocas\n", comparacoes, trocas);
            };
        }
		// "imprimir" mostra o heap na ordem em que esta no vetor
        else if (op == imprimir){
			if (N == 0){
				printf("Nao ha nada para imprimir aqui...\n");
			}
			else{
				ImprimeHeap(filaEmbarque, N);
			};
        }
			// "inicheap" esvazia o aviao
        else if (op == inicheap){
            InicHeap(&N);
            printf("Uma nova fila de embarque foi iniciada!\n");
        }
		/* "heapfy" mostra a construcao de um heap a partir de um vetor desordenado
		como o aviao ja eh heap, nao serviria */
        else if (op == heapfy){
            /* monta um vetor com prioridades embaralhadas na copia */
            for (i = 1; i <= CAPACIDADE; i++) 
				livre[i] = i;
            Embaralhar(livre, CAPACIDADE);
            for (i = 1; i <= CAPACIDADE; i++){
                sprintf(copia[i].nome, "Passageiro %d", i);
                copia[i].prioridade = livre[i];
            };
            printf("Vetor desordenado:\n");
            ImprimeHeap(copia, CAPACIDADE);
            if (ChecaHeap(copia, CAPACIDADE)) printf("Eh um heap.\n");
            else printf("NAO eh um heap.\n");

            comparacoes = 0; trocas = 0;
            Heapfy(copia, CAPACIDADE);
            printf("Depois do Heapfy:\n");
            ImprimeHeap(copia, CAPACIDADE);
            if (ChecaHeap(copia, CAPACIDADE)) printf("Eh um heap.\n");
            else printf("NAO eh um heap.\n");
            printf("Heapfy: %ld comparacoes, %ld trocas\n", comparacoes, trocas);
        }
			// "checar" confere se a fila do aviao eh um heap valido
        else if (op == checar){
            if (ChecaHeap(filaEmbarque, N)) printf("O vetor \"Fila de Embarque\" eh um heap.\n");
            else printf("O vetor \"FIla de Enbarque\" NAO eh um heap.\n");
        }
		// "gerar" compara quicksort, insertsort e heapsort
        else if (op == gerar){
            int base[TAM_VETOR + 1]; // vetor aleatorio original (n eh alterado)
			int vet[TAM_VETOR + 1]; // copia que cada algoritmo ordena
            passageiro hs[TAM_VETOR + 1]; // versao em passageiro para o heapsort
            GeraVetor(base, TAM_VETOR);
            printf("Vetor com %d elementos aleatorios gerado.\n", TAM_VETOR);
			// cada algoritmo recebe uma copia do mesmo vetor com os contadores zerados
            for (i = 1; i <= TAM_VETOR; i++) 
				vet[i] = base[i];
            comparacoes = 0; trocas = 0;
            QuickSort(vet, 1, TAM_VETOR);
            printf("QuickSort:  %ld comparacoes, %ld trocas\n", comparacoes, trocas);

            for (i = 1; i <= TAM_VETOR; i++) 
				vet[i] = base[i];
            comparacoes = 0; trocas = 0;
            InsertSort(vet, TAM_VETOR);
            printf("InsertSort: %ld comparacoes, %ld trocas\n", comparacoes, trocas);
			/* o heapsort trabalha com passageiros, entao os numeros do vetor
				sao copiados para o campo prioridade */
            for (i = 1; i <= TAM_VETOR; i++) 
				hs[i].prioridade = base[i];
            comparacoes = 0; trocas = 0;
            HeapSort(hs, TAM_VETOR);
            printf("HeapSort:   %ld comparacoes, %ld trocas\n", comparacoes, trocas);
		}
		// qualquer outro numero nao existe no menu
		else{ 
			printf("Opcao invalida \n ");
		}
		// mostra o menu de novo e le a proxima opcao
		ImprimeMenu();
		scanf("%d", &op);
	} 
	return 0;
}
