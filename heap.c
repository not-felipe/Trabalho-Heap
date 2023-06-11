#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 30

int totalElementos = 0;

int indiceFilhoEsq(int x) { // x sendo o indice do pai
  int indice = (2 * x) + 1;
  if (x >= totalElementos || indice >= totalElementos)
    return -1;
  else
    return indice;
}

int indiceFilhoDir(int x) {
  int indice = (2 * x) + 2;
  if (x >= totalElementos || indice >= totalElementos)
    return -1;
  else
    return indice;
}

int indicePai(int x) {
  int indice =
      (int)floor((x - 1) / 2); // Pega o piso da divisão, ja que o indice do pai
                               // é a parte inteira de (i-1)/2
  if (x <= 0 || x >= totalElementos)
    return -1;
  else
    return indice;
}

void ajustarSubindo(int *heap, int pos) {
  if (pos != -1) { // NULL
    int pai = indicePai(pos);
    if (pai != -1) {
      if (heap[pos] < heap[pai]) { // Nó maior que pai?
        int aux = heap[pos];
        heap[pos] = heap[pai];
        heap[pai] = aux;
        ajustarSubindo(heap, pai);
      }
    }
  }
}

void ajustarDescendo(int *heap, int pos) {
  if (pos != -1 && indiceFilhoEsq(pos) != -1) {
    // Descobrindo o maior filho
    int indiceMaiorFilho = indiceFilhoEsq(pos);
    if (indiceFilhoDir(pos) != -1 &&
        heap[indiceFilhoDir(pos)] < heap[indiceMaiorFilho])
      indiceMaiorFilho = indiceFilhoDir(pos);

    if (heap[indiceMaiorFilho] < heap[pos]) {
      int aux = heap[pos];
      heap[pos] = heap[indiceMaiorFilho];
      heap[indiceMaiorFilho] = aux;
      ajustarDescendo(heap, indiceMaiorFilho);
    }
  }
}

int remover(int *heap) {
  if (totalElementos == 0) { // nao tem elemento para remover
    return -1;
  } else {
    int retorno = heap[0];
    heap[0] = heap[totalElementos - 1];
    totalElementos--;
    ajustarDescendo(heap, 0);
    return retorno;
  }
}

void Inserir(int *heap, int x) {
  heap[totalElementos] = x;
  totalElementos++;

  ajustarSubindo(heap, totalElementos - 1);
}

int main() {

  int heap[MAX];
  int option;

  do {
    printf("\nMenu ---- Heap\n[1] Inserir um elemento x na heap\n[2] Remover "
           "um elemento\n[3] Imprimir a heap\n[4] Sair\n[->] ");
    scanf("%d", &option);
    switch (option) {
    case 1: {
      int x;
      printf("Digite o elemento a ser inserido: ");
      scanf("%d", &x);
      Inserir(heap, x);
      break;
    }
    case 2: {
      int elementoRemovido = remover(heap);
      if (elementoRemovido != -1)
        printf("Elemento %d removido com sucesso!\n", elementoRemovido);
      else
        printf("Nao ha elemento para ser removido!\n");
      break;
    }
    case 3:
      printf("Representação da heap\n");
      for (int i = 0; i < totalElementos; i++) {
        printf("%d ", heap[i]);
      }
      printf("\n");
      break;
    case 4:
      printf("Programa encerrado!\n");
      exit(1);
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (option != 4);

  return 0;
}
