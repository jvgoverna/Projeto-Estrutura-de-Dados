#ifndef PESQUISA__H
#define PESQUISA__H

#include "Cadastrar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct EABB{
    int valor;
    struct EABB *esq;
    struct EABB *dir;
    struct EABB *pai;
} EABB;//(Vertice)

typedef struct ABB {
    EABB *raiz;
    int qtde;
} ABB;//(Arvore)


ABB *cria_arvore() {
    ABB *arvore = (ABB *) malloc(sizeof(ABB));
    arvore->raiz = NULL;
    arvore->qtde = 0;

    return arvore;
}

EABB *cria_EABB(ABB *arvore, int valor) {
    EABB *novo = (EABB *) malloc(sizeof(EABB));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->valor = valor;
    return novo;
}


void in_ordem(EABB *raiz) {
    if (raiz != NULL) {
        in_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        in_ordem(raiz->dir);
    }
}

void inserirnaraiz(ABB *arvore, int valor) {
    EABB *novo = cria_EABB(arvore, valor);
    // Se a ávore estiver vazia
    if(arvore->qtde == 0){
        arvore->raiz = novo;// Novo vértice é a raiz da árvore
        arvore->qtde++;
    }else{ // Árvore não vazia
        EABB *atual = arvore->raiz;
        EABB *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if(valor < atual->valor){
                atual = atual->esq;
            }else{
                atual = atual->dir;
            }
        }
        if (valor < atual->valor) {
            anterior->esq = novo;
        }else{
            anterior->dir = novo;
        }
        novo->pai = anterior;
    }
}





void menuPesquisar(){
    char option[4];
    Registro registro;
    while(1){
        puts("------------------------------------------------------");
        puts("1 - Mostrar registros ordenados por ano de registro");
        puts("2 - Mostrar registros ordenados por mês de registro");
        puts("3 - Mostrar registros ordenados por dia de registro");
        puts("4 - Mostrar registros ordenados por idade do paciente");
        puts("0 - Voltar ao Menu Principal");
        puts("------------------------------------------------------");
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
                puts("--------------------------- Opção 1 ---------------------------");
                limparTela();
                ABB *arvoreAno = cria_arvore();
                FILE *arquivo;
                arquivo = fopen("CadastrosBin.txt", "rb");
                if(arquivo == NULL){
                  puts("ERRO! Arquivo vazio!");
                  return;
                }
                while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {
                  inserirnaraiz(arvoreAno,registro.entrada.ano);
                }
                fclose(arquivo);
                puts("Em ordem:");
                in_ordem(arvoreAno->raiz);
                printf("\n");
                break;
            case '2':
                puts("--------------------------- Opção 2 ---------------------------");
                limparTela();
                ABB *arvoreMes = cria_arvore();
                FILE *arquivo2;
                arquivo2 = fopen("CadastrosBin.txt", "rb");
                if(arquivo2 == NULL){
                  puts("ERRO! Arquivo vazio!");
                  return;
                }
                while (fread(&registro, sizeof(struct Registro), 1, arquivo2)) {
                  inserirnaraiz(arvoreMes,registro.entrada.mes);
                }
                fclose(arquivo2);
                in_ordem(arvoreMes->raiz);
                printf("\n");
                break;
            case '3':
                puts("--------------------------- Opção 3 ---------------------------");
                limparTela();
                ABB *arvoreDia = cria_arvore();
                FILE *arquivo3;
                arquivo3 = fopen("CadastrosBin.txt", "rb");
                if(arquivo3 == NULL){
                  puts("ERRO! Arquivo vazio!");
                  return;
                }
                while (fread(&registro, sizeof(struct Registro), 1, arquivo3)) {
                  inserirnaraiz(arvoreDia,registro.entrada.dia);
                }
                fclose(arquivo);
                puts("Em ordem:");
                in_ordem(arvoreDia->raiz);
                printf("\n");
                break;
              case '4':
                puts("--------------------------- Opção 4 ---------------------------");
                limparTela();
                ABB *arvoreIdade = cria_arvore();
                arquivo = fopen("CadastrosBin.txt", "rb");
                if(arquivo == NULL){
                  puts("ERRO! Arquivo vazio!");
                  return;
                }
                while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {
                  inserirnaraiz(arvoreIdade,registro.idade);
                }
                fclose(arquivo);
                puts("Em ordem:");
                in_ordem(arvoreIdade->raiz);
                printf("\n");
                break;
            }
        }
    }
}
#endif