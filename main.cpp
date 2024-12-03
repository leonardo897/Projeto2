#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Função para ler o arquivo de entrada
void lerEntrada(const char* nome_arquivo, int* n, int particao[MAX][MAX], int* k) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Lendo o número de elementos n
    fscanf(arquivo, "%d", n);

    // Lendo a partição (subconjuntos)
    fscanf(arquivo, "%d", k);
    for (int i = 0; i < *k; i++) {
        int tamanho_subconjunto;
        fscanf(arquivo, "%d", &tamanho_subconjunto);
        for (int j = 0; j < tamanho_subconjunto; j++) {
            fscanf(arquivo, "%d", &particao[i][j]);
        }
    }

    fclose(arquivo);
}

// Função para encontrar o representante de um conjunto usando "representante" (Busca)
int representante(int elemento, int particao[MAX][MAX], int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < MAX; j++) {
            if (particao[i][j] == elemento) {
                return particao[i][0]; // Retorna o primeiro elemento do subconjunto como representante
            }
        }
    }
    return -1; // Caso não encontre o elemento
}

// Função para encontrar a posição de um conjunto
int posicao(int elemento, int particao[MAX][MAX], int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < MAX; j++) {
            if (particao[i][j] == elemento) {
                return i; // Retorna a posição do conjunto
            }
        }
    }
    return -1; // Caso não encontre o elemento
}

// Consultar o tamanho de um conjunto
int tamanhoVetor(int vetor[]){
    int tamanho = 0;

    while(vetor[tamanho] != 0 && tamanho < MAX){
        tamanho++;
    }

    return tamanho;
}

// Função para realizar a união de dois subconjuntos que contêm os elementos
void unir(int elemento1, int elemento2, int particao[MAX][MAX], int* k) {
    int rep1 = representante(elemento1, particao, *k);
    int rep2 = representante(elemento2, particao, *k);

    if (rep1 == rep2) {
        printf("Os elementos ja estao no mesmo conjunto.\n");
        return;
    }

    // Encontrando os índices dos subconjuntos que contêm os representantes
    int indice_rep1 = -1, indice_rep2 = -1;
    for (int i = 0; i < *k; i++) {
        if (particao[i][0] == rep1) {
            indice_rep1 = i;
        }
        if (particao[i][0] == rep2) {
            indice_rep2 = i;
        }
    }

    // Realiza a união
    if (indice_rep1 != -1 && indice_rep2 != -1) {
        // Encontrar o tamanho dos subconjuntos
        int tamanho_rep1 = tamanhoVetor(particao[indice_rep1]);
        int tamanho_rep2 = tamanhoVetor(particao[indice_rep2]);

        // Coloca os elementos do subconjunto 2 no subconjunto 1
        for (int i = 0; i < tamanho_rep2; i++) {
            particao[indice_rep1][tamanho_rep1 + i] = particao[indice_rep2][i];
        }

        for (int i = 0; i < tamanhoVetor(particao[*k - 1]); i++) {
            particao[indice_rep2][i] = particao[*k - 1][i];
            particao[*k - 1][i] = 0; // Apaga o subconjunto 2
        }

        // Decrementa o número de subconjuntos
        (*k)--;
    }
}

// Função para imprimir o menu
void menu() {
    printf("Escolha uma opcaoo:\n");
    printf("1. Consultar representante de um conjunto\n");
    printf("2. Unir dois subconjuntos\n");
    printf("3. Ordenar um subconjunto\n");
    printf("4. Exibir todos os subconjuntos\n");
    printf("0. Sair\n");
}

// Função de ordenação Bubble Sort
void bubbleSort(int vetor[], int n) {
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // Troca de elementos
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

// Função de ordenação Insertion Sort
void insertionSort(int vetor[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

// Função de mesclagem para Merge Sort
void mescla(int vetor[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Vetores temporários
    int esquerdo[n1], direito[n2];

    // Copiar dados para os vetores temporários
    for (i = 0; i < n1; i++) {
        esquerdo[i] = vetor[inicio + i];
    }
    for (j = 0; j < n2; j++) {
        direito[j] = vetor[meio + 1 + j];
    }

    // Mesclar os vetores temporários
    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (esquerdo[i] <= direito[j]) {
            vetor[k] = esquerdo[i];
            i++;
        } else {
            vetor[k] = direito[j];
            j++;
        }
        k++;
    }

    // Copiar os elementos restantes, se houver
    while (i < n1) {
        vetor[k] = esquerdo[i];
        i++;
        k++;
    }
    while (j < n2) {
        vetor[k] = direito[j];
        j++;
        k++;
    }
}

// Função de ordenação Merge Sort
void mergeSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        mescla(vetor, inicio, meio, fim);
    }
}

// Função de particionamento para Quick Sort
int particiona(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];
    int i = (inicio - 1);
    int j, aux;

    for (j = inicio; j <= fim - 1; j++) {
        if (vetor[j] <= pivo) {
            i++;
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
        }
    }

    aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = aux;

    return (i + 1);
}

// Função de ordenação Quick Sort
void quickSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pivo - 1); // Aplica o quick sort na primeira parte
        quickSort(vetor, pivo + 1, fim); // Aplica o quick sort na segunda parte
    }
}

// Imprime os elementos de um conjunto
void exibirConjunto(int vetor[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int n, k;
    int particao[MAX][MAX] = {0};

    // Le o arquivo de entrada
    lerEntrada("entrada.txt", &n, particao, &k);

    int opcao;
    do {
        menu(); // Exibe o menu
        scanf("%d", &opcao); // Le a entrada do usuario

        if (opcao == 1) {
            int elemento;
            printf("Digite o elemento para consultar seu representante: ");
            scanf("%d", &elemento);

            int rep = representante(elemento, particao, k); // Pega o representante do conjunto que contém o elemento desejado

            if (rep != -1) {
                printf("O representante do subconjunto que contem %d: %d\n", elemento, rep);
            }
            else {
                printf("Elemento nao encontrado na particaoo.\n");
            }
        }
        else if (opcao == 2) {
            int elemento1, elemento2;
            printf("Digite os dois elementos para unir os subconjuntos: ");
            scanf("%d %d", &elemento1, &elemento2);

            unir(elemento1, elemento2, particao, &k); // Une os conjuntos que contém os elementos desejados

            printf("Uniao realizada.\n");
        }

        else if (opcao == 3) {
            int elemento;
            printf("Digite o elemento para encontrar o subconjunto para ordenacao: ");
            scanf("%d", &elemento);

            int pos = posicao(elemento, particao, k); // A posição do conjunto que contém o elemento desejado
            int tamanho = tamanhoVetor(particao[pos]); // Tamanho do conjunto que contém o elemento

            if (pos != -1) {
                printf("Escolha o tipo de ordenacao:\n");
                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Merge Sort\n");
                printf("4. Quick Sort\n");

                int tipo;
                scanf("%d", &tipo);

                printf("Conjunto antes da ordenacao:\n");
                exibirConjunto(particao[pos], tamanho);

                if (tipo == 1) {
                    bubbleSort(particao[pos], tamanho);
                }

                else if (tipo == 2) {
                    insertionSort(particao[pos], tamanho);
                }

                else if (tipo == 3) {
                    mergeSort(particao[pos], 0, tamanho - 1);
                }

                else if (tipo == 4) {
                    quickSort(particao[pos], 0, tamanho - 1);
                }

                printf("Conjunto apps a ordenacao:\n"); // Imprime o conjuto antes e depois da ordenação
                exibirConjunto(particao[pos], tamanho);
            }
            else {
                printf("Elemento nao encontrado na particao.\n");
            }
        }

        else if (opcao == 4) {
            // Imprime todos os conjuntos
            for (int i = 0; i < k; i++){
                exibirConjunto(particao[i], tamanhoVetor(particao[i]));
            }
        }

    } while (opcao != 0);

    return 0;
}
