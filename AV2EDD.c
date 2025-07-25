#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um aluno            
typedef struct aluno {
    char nome[100];
    char matricula[20];
    float nota1, nota2;
    char disciplina[100];
    char professor[100];
    struct aluno *prox; // ponteiro para o proximo
} Aluno;

// Estrutura da fila (implementada com lista encadeada)
typedef struct {
    Aluno *inicio;
    Aluno *fim;
} Fila;

// Estrutura para armazenar resultado na pilha
typedef struct {
    char resultado[150];
} Resultado;

#define TAM_PILHA 100

// Estrutura da pilha (implementada com vetor)
typedef struct {
    Resultado itens[TAM_PILHA];
    int topo;
} Pilha;


Fila* criarFila() {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}


void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

void empilhar(Pilha *p, char *texto) {
    if (p->topo < TAM_PILHA - 1) {
        p->topo++;
        strcpy(p->itens[p->topo].resultado, texto);
    }
}

// Adiciona um aluno na fila (lista encadeada)
void enfileirar(Fila *f) {
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    printf("Nome: ");
    fgets(novo->nome, 100, stdin);
    strtok(novo->nome, "\n");

    printf("Matricula: ");
    fgets(novo->matricula, 20, stdin);
    strtok(novo->matricula, "\n");

    printf("Disciplina: ");
    fgets(novo->disciplina, 100, stdin);
    strtok(novo->disciplina, "\n");

    printf("Professor: ");
    fgets(novo->professor, 100, stdin);
    strtok(novo->professor, "\n");

    printf("Nota 1: ");
    scanf("%f", &novo->nota1);
    printf("Nota 2: ");
    scanf("%f", &novo->nota2);
    getchar();

    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

// Lista alunos de forma recursiva
void listarRecursivo(Aluno *aux, Pilha *p) {
    if (aux == NULL) return;

    float media = (aux->nota1 + aux->nota2) / 2.0;
    printf("\nNome: %s", aux->nome);
    printf("\nMatricula: %s", aux->matricula);
    printf("\nDisciplina: %s", aux->disciplina);
    printf("\nProfessor: %s", aux->professor);
    printf("\nNota 1: %.2f", aux->nota1);
    printf("\nNota 2: %.2f", aux->nota2);
    printf("\nMedia: %.2f", media);
    if (media >= 7.0) {
        printf(" (Aprovado)\n");
        char texto[150];
        sprintf(texto, "%s - Aprovado", aux->nome);
        empilhar(p, texto);
    } else {
        printf(" (Reprovado)\n");
        char texto[150];
        sprintf(texto, "%s - Reprovado", aux->nome);
        empilhar(p, texto);
    }

    listarRecursivo(aux->prox, p);
}

void exibirPilha(Pilha *p) {
    printf("\nResumo (Pilha de resultados):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%s\n", p->itens[i].resultado);
    }
}

// Pesquisa um aluno por matricula
void pesquisarPorMatricula(Fila *f, char *matriculaBusca) {
    Aluno *aux = f->inicio;
    int encontrado = 0;

    while (aux != NULL) {
        if (strcmp(aux->matricula, matriculaBusca) == 0) {
            printf("\nAluno encontrado:");
            printf("\nNome: %s", aux->nome);
            printf("\nMatricula: %s", aux->matricula);
            printf("\nDisciplina: %s", aux->disciplina);
            printf("\nProfessor: %s", aux->professor);
            printf("\nNota 1: %.2f", aux->nota1);
            printf("\nNota 2: %.2f\n", aux->nota2);
            encontrado = 1;
            break;
        }
        aux = aux->prox;
    }

    if (!encontrado) {
        printf("\nAluno com essa matricula nao encontrado.\n");
    }
}

int main() {
    Fila *filaAlunos = criarFila(); 
    Pilha pilhaResultados; 
    inicializarPilha(&pilhaResultados);

    int op;
    do {
        printf("\n1 - Cadastrar Aluno");
        printf("\n2 - Listar Alunos com Medias (Recursivo)");
        printf("\n3 - Mostrar Pilha de Resultados");
        printf("\n4 - Pesquisar Aluno por Matricula");
        printf("\n0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();

        if (op == 1) {
            enfileirar(filaAlunos);
        } else if (op == 2) {
            listarRecursivo(filaAlunos->inicio, &pilhaResultados);
        } else if (op == 3) {
            exibirPilha(&pilhaResultados);
        } else if (op == 4) {
            char busca[20];
            printf("Digite a matricula para pesquisar: ");
            fgets(busca, 20, stdin);
            strtok(busca, "\n");
            pesquisarPorMatricula(filaAlunos, busca);
        }

    } while (op != 0);

    return 0;
}
