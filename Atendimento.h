#ifndef ATENDIMENTO__H
#define ATENDIMENTO__H
//includes utilizados
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
  Efila *novo = (Efila *) malloc(sizeof(Efila));  //Reservo um espaço na memória para armazenar a Efila
  novo->anterior = NULL;  //seta o anterior para nulo (não tem nada)
  novo->proximo = NULL; //seta o proximo para nulo (não tem nada)
  novo->dados = dados; //seto o item do struct da Efila (dados) para receber o registro
  return novo;
}

Fila *inicializa_fila() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));  //Reservo um espaço na memória para armazenar a fila
  fila->head = NULL; //seta o head para nulo (não tem nada)
  fila->tail = NULL;//seta a tail para nulo (não tem nada)
  fila->qtde = 0; //seta a quantidade de elmentos para nulo (não tem nada)
  return fila;
}

void enfileirar(Fila *fila, Registro dados) { //função de enfileirar (FI e FO)
  Efila *novo = inicializa_Efila(dados); //crio uma nova Efila
  if (fila->qtde == 0) { //se a efila está vazia , crio uma nova head e tail
    fila->head = novo;
    fila->tail = novo;

  } else { //se não
    novo->anterior = fila->tail; //o elemento anterior será igual ao ponteiro da fila tail
    fila->tail->proximo = novo; // o próximo da cauda é o novo
  }
  fila->tail = novo;
  fila->qtde++; //aumenta a quantidade de elementos
}


void enfilerarPaciente(Fila *fila , Registro registro, char referencia[]) { //coloco os pacientes
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
  if(verificador == 0){ 
    puts("Pessoa não foi cadastrada!");
  }
  fclose(arquivo);
}
void mostrarFila(Fila *fila){ //mostro os pacientes enfileirados
  Efila *atual = fila->head; //crio uma Efila que será de inicio igual ao head da fila

  if(fila->qtde ==0){ //fila vazia
    puts("Não há pessoa na fila!");
  }else{ //fila não vazia, mostro o número de pessoas nela
  printf("\nNúmero de pessoa na Fila: %d\n", fila->qtde);
  printf("\nHead -> \n");
  while(atual != NULL){ //atualizo o nome das pessoas que estão enfileiradas
    printf("%s", atual->dados.nome);
    atual = atual->proximo;
  }

  printf("<- Tail\n");
  }
}


void desenfileirar(Fila *fila){ //desenfilero seguindo o (FI Fo)
  if(fila->qtde != 0){ //fila não vazia
    //int valor = fila->head->dados;
    Efila *liberar = fila->head;

    if(fila->qtde == 1){ //apenas um valor na fila
      fila->head = NULL; //coloco o head e tail para nulo para poder tirar o paciente
      fila->tail = NULL;
      
    }else{ //se a fila estiver com mais gente
      fila->head = fila->head->proximo; //o head será igual ao próximo
      fila->head->anterior = NULL; //e o anterior do head não existe mais
    }
    fila->qtde--; //diminuo a quantidade de pessoas
    free(liberar); //libero memoria
    puts("Paciente desenfileirado");
  }else{ 
    printf("Fila vazia\n");
  }
}

void menuAtendimento(){ //menu atendimento mesma lógica de verificar se o usuário digitou corretamente
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
                fgets(referencia, sizeof(referencia), stdin);//controle para ver se o nome está no arquivo
                enfilerarPaciente(fila,registro, referencia);//enfilero
              
                break;
            case '2':
                puts("---------- Opção 2 ----------");
                limparTela();
                desenfileirar(fila); //desenfilero
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