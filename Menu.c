#include <stdio.h>
#include "Sobre.h"
#include "Cadastrar.h"


void limparBufferInput(){
    while(getchar() != '\n');
}


int main(){
    Data *data = startData();
    char option[4];
    while(1){
        puts("-------------------------------");
        puts("0 - Sair");
        puts("1 - Cadastrar");
        puts("2 - Atendimento");
        puts("3 - Pesquisa");
        puts("4 - Carregar / Salvar");
        puts("5 - Sobre");
        puts("-------------------------------");
        fgets(option,sizeof(option),stdin);

        if(option[0] > '5' || option[0] < '0'){
            puts("ERRO Digite uma opção válida!");
        }else if (option[1] >= '0'){
            puts("ERRO Digite uma opção válida!");
        }else{
            switch (option[0]){
            case '0':
                puts("Saindo...");
                return 0;
                break;
            case '1':
                puts("---------- Opção 1 ----------");
                teste(data);
                limparBufferInput();
                break;
            case '2':
                puts("---------- Opção 2 ----------");
                break;
            case '3':
                puts("---------- Opção 3 ----------");
                break;
            case '4':
                puts("---------- Opção 4 ----------");
                break;
            case '5':
                puts("---------- Opção 5 ----------");
                sobre();
                break;
            }
        }
    }
}