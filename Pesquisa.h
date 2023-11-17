#ifndef PESQUISA__H
#define PESQUISA__H

#include "Cadastrar.h" //Includes utilizados
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura do vertice
typedef struct EABB {
  int valor;
  char nome[20];
  struct EABB *esq;
  struct EABB *dir;
  struct EABB *pai;
} EABB; 

//estrutura da arvore
typedef struct ABB {
  EABB *raiz;
  int qtde;
} ABB; //(Arvore)

//inicialização da arvore
ABB *cria_arvore() {
  ABB *arvore = (ABB *)malloc(sizeof(ABB)); //Reservo um espaço na memória para armazenar a Árvore
  arvore->raiz = NULL; //seta a raiz da árvore como vazia 
  arvore->qtde = 0; //seta a quantidade de elementos inicial para 0

  return arvore;
}

//inicialização do vertice
EABB *cria_EABB(ABB *arvore, int valor, char nome[]) { //Cria o vértice
  EABB *novo = (EABB *)malloc(sizeof(EABB));
  novo->dir = NULL; 
  novo->esq = NULL; 
  novo->pai = NULL; 
  novo->valor = valor;
  // Copia no máximo 19 caracteres de 'nome' para 'novo->nome'
  strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
  novo->nome[sizeof(novo->nome) - 1] = '\0'; // Garante que a string é terminada corretamente (enter)

  return novo;
}


//mostrar a arvore binaria na ordem crescente, usado recursao para continuar percorrendo as vertices até a ponta
void in_ordem(EABB *raiz) {
  if (raiz != NULL) {
    in_ordem(raiz->esq); 
    printf("%s-> %d | \n", raiz->nome, raiz->valor); 
    in_ordem(raiz->dir);
  }
}

//inserir um valor com os parametros de arvire, numero e nome
void inserirnaraiz(ABB *arvore, int valor, char nome[]) {
  EABB *novo = cria_EABB(arvore, valor, nome);
  EABB* atual = arvore->raiz;
  //quando não tem nada, cria o começo da arvore
  if(arvore->raiz == NULL){
    arvore->raiz = novo;
    arvore->qtde++; //aumenta a quantidade de elementos
    return;
  }

  //quando ja tem raiz 
  while(1){
    if(valor < atual->valor){
      //inserir na esquerda valor atual < pai
      if(atual->esq == NULL){
        atual->esq = novo;
        novo->pai = atual;
        arvore->qtde++;
        return;
      } else {
        atual = atual->esq; //quando há filho do filho da esquerda
      }
    } else {
      //inserir na direita valor atual > pai
      if(atual->dir == NULL){

        atual->dir = novo;
        novo->pai = atual;
        arvore->qtde++;
        return;
      } else {
        atual = atual->dir; //quando há filho do filho da direita
      }
    }
  }
}

//menu pesquisar mesma lógica de verificar se o usuário digitou a opção correta
void menuPesquisar() {
  char option[4];
  Registro registro;
  while (1) {
    puts("------------------------------------------------------");
    puts("1 - Mostrar registros ordenados por ano de registro");
    puts("2 - Mostrar registros ordenados por mês de registro");
    puts("3 - Mostrar registros ordenados por dia de registro");
    puts("4 - Mostrar registros ordenados por idade do paciente");
    puts("0 - Voltar ao Menu Principal");
    puts("------------------------------------------------------");
    fgets(option, sizeof(option), stdin);

    if (option[0] > '5' || option[0] < '0') {
      puts("ERRO Digite uma opção válida!");
    } else if (option[1] >= '0') {
      puts("ERRO Digite uma opção válida!");
    } else {
      switch (option[0]) {
      case '0':
        limparTela();
        puts("Voltando ao Menu Principal...");
        return;
        break;
      case '1':
        puts("--------------------------- Opção 1 ---------------------------");
        limparTela();
        //cria a arvore binaria do ano
        ABB *arvoreAno = cria_arvore();
        FILE *arquivo;
        arquivo = fopen("CadastrosBin.txt", "rb"); //abre o arquivo em modo de leitura
        if (arquivo == NULL) { //arquvo vazio
          puts("ERRO! Arquivo vazio!");
          return;
        }
        //adiciona os registros na arvore 
        while (fread(&registro, sizeof(struct Registro), 1, arquivo)) { //percorre o arquivo para inserir
          inserirnaraiz(arvoreAno, registro.entrada.ano, registro.nome);
        }
        fclose(arquivo);
        //mostra a arvore em ordem
        puts("Em ordem:");
        in_ordem(arvoreAno->raiz);
        printf("\n");
        break;
      case '2':
        puts("--------------------------- Opção 2 ---------------------------");
        limparTela();
        //cria a arvore binaria do mes
        ABB *arvoreMes = cria_arvore();
        FILE *arquivo2;
        arquivo2 = fopen("CadastrosBin.txt", "rb");
        if (arquivo2 == NULL) {
          puts("ERRO! Arquivo vazio!");
          return;
        }
        //adiciona os registros na arvore 
        while (fread(&registro, sizeof(struct Registro), 1, arquivo2)) { //percorre o arquivo para inserir
          inserirnaraiz(arvoreMes, registro.entrada.mes, registro.nome);
        }
        fclose(arquivo2);
        //mostra a arvore em ordem
        in_ordem(arvoreMes->raiz);
        printf("\n");
        break;
      case '3':
        puts("--------------------------- Opção 3 ---------------------------");
        limparTela();
        //cria a arvore binaria do dia
        ABB *arvoreDia = cria_arvore();
        FILE *arquivo3;
        arquivo3 = fopen("CadastrosBin.txt", "rb");
        if (arquivo3 == NULL) {
          puts("ERRO! Arquivo vazio!");
          return;
        }
        //adiciona os registros na arvore 
        while (fread(&registro, sizeof(struct Registro), 1, arquivo3)) { //percorre o arquivo para inserir
          inserirnaraiz(arvoreDia, registro.entrada.dia, registro.nome);
        }
        fclose(arquivo);
        puts("Em ordem:");
        //mostra a arvore em ordem
        in_ordem(arvoreDia->raiz);
        printf("\n");
        break;
      case '4':
        puts("--------------------------- Opção 4 ---------------------------");
        limparTela();
        //cria a arvore binaria da idade
        ABB *arvoreIdade = cria_arvore();
        arquivo = fopen("CadastrosBin.txt", "rb");
        if (arquivo == NULL) {
          puts("ERRO! Arquivo vazio!");
          return;
        }
        //adiciona os registros na arvore 
        while (fread(&registro, sizeof(struct Registro), 1, arquivo)) { //percorre o arquivo para inserir
          inserirnaraiz(arvoreIdade, registro.idade, registro.nome);
        }
        fclose(arquivo);
        puts("Em ordem:");
        //mostra a arvore em ordem
        in_ordem(arvoreIdade->raiz);
        printf("\n");
        break;
      }
    }
  }
}
#endif