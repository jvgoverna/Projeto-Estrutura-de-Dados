#ifndef ATENDIMENTO__H
#define ATENDIMENTO__H

#include "Cadastrar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Efila {
  Registro dados;
  struct Efila *proximo;
  struct Efila *anterior;
}Efila;

typedef struct {
  Efila *head;
  Efila *tail;
  int qtde;
}Fila;

Efila *inicializa_Efila(Registro dados) {
  Efila *novo = (Efila *) malloc(sizeof(Efila));
  novo->anterior = NULL;
  novo->proximo = NULL;
  novo->dados = dados;
  return novo;
}

Fila *inicializa_fila() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->head = NULL;
  fila->tail = NULL;
  fila->qtde = 0;
  return fila;
}

void enfileirar(Fila *fila, Registro dados) {
  Efila *novo = inicializa_Efila(dados);
  if (fila->qtde == 0) {
    fila->head = novo;
    fila->tail = novo;

  } else {
    novo->anterior = fila->tail;
    fila->tail->proximo = novo;
  }
  fila->tail = novo;
  fila->qtde++;
}


void enfilerarPaciente(Fila *fila , Registro registro, char referencia[]) {
  int verificador = 0;
  FILE *arquivo;
  arquivo = fopen("CadastrosBin.txt", "rb");
  if(arquivo == NULL){
    puts("ERRO! Arquivo vazio!");
    return;
  }
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {
    if (strcmp(referencia, registro.nome) == 0) { //Se o Nome que pesquisar for igual ao escrito no arquivo retorna 0, oq quer dizer que é igual!
      verificador = 1; //encontrou a pessoa!
      enfileirar(fila, registro);
      puts("Paciente foi colocado na fila com sucesso!");
    }
  }
  if(verificador == 0){ //
    puts("Pessoa não foi cadastrada!");
  }
  fclose(arquivo);
}
void mostrarFila(Fila *fila){
  Efila *atual = fila->head;

  if(fila->qtde ==0){
    puts("Não há pessoa na fila!");
  }else{
  printf("\nNúmero de pessoa na Fila: %d\n", fila->qtde);
  printf("\nHead -> \n");
  while(atual != NULL){
    printf("%s", atual->dados.nome);
    atual = atual->proximo;
  }

  printf("<- Tail\n");
  }
}


void desenfileirar(Fila *fila){
  if(fila->qtde != 0){
    //int valor = fila->head->dados;
    Efila *liberar = fila->head;

    if(fila->qtde == 1){ //apenas um valor na fila
      fila->head = NULL;
      fila->tail = NULL;
      
    }else{
      fila->head = fila->head->proximo;
      fila->head->anterior = NULL;
    }
    fila->qtde--;
    free(liberar);
    puts("Paciente desenfileirado");
  }else{
    printf("Fila vazia\n");
  }
}

void menuAtendimento(){
    char option[4];
    Fila *fila = inicializa_fila();
    Registro registro;
    while(1){
        puts("-------------------------------");
        puts("1 - Enfileirar Pacientes");
        puts("2 - Desenfileirar Pacientes");
        puts("3 - Mostrar Fila");
        puts("0 - Voltar ao Menu Principal");
        puts("-------------------------------");
        fgets(option,sizeof(option),stdin);

        if(option[0] > '5' || option[0] < '0'){
            puts("ERRO Digite uma opção válida!");
        }else if (option[1] >= '0'){
            puts("ERRO Digite uma opção válida!");
        }else{
            switch (option[0]){
            case '0':
                limparTela();
                puts("Voltando ao Menu Principal...");
                return;
                break;
            case '1':
                puts("---------- Opção 1 ----------");
                limparTela();
                char referencia[20];
                printf("Digite o nome do paciente cadastrado: ");
                fgets(referencia, sizeof(referencia), stdin);
                enfilerarPaciente(fila,registro, referencia);
              
                break;
            case '2':
                puts("---------- Opção 2 ----------");
                limparTela();
                desenfileirar(fila);
                break;
            case '3':
                puts("---------- Opção 3 ----------");
                limparTela();
                //mostrar a fila
                mostrarFila(fila);
                break;
            }
        }
    }
}



#endif