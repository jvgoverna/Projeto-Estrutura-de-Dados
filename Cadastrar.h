#ifndef CADASTRAR__H
#define CADASTRAR__H
#include <stdio.h>
#include <stdlib.h>

typedef struct Data{
    int dia;
    int mes;
    int ano;
}Data;

Data *startData(){
    Data *data = malloc(sizeof(Data));
    data->ano = 0;
    data->mes = 0;
    data->dia = 0;
    return data;
}

void limpaBufferInput(){
    while(getchar() != '\n');
}

void teste(Data *data){
    puts("Dia");
    scanf("%d", &data->dia);
    puts("Mes");
    scanf("%d", &data->mes);
    puts ("Ano");
    scanf("%d", &data->ano);
    printf("Dia %d Mes %d Ano %d\n", data->dia, data->mes, data->ano);
}

void menuCadastrar(){
    Data *data = startData();
    char option[4];
    while(1){
        puts("-------------------------------");
        puts("0 - Voltar ao menu principal");
        puts("1 - Cadastrar novo paciente");
        puts("2 - Consultar paciente cadastrado");
        puts("3 - Mostrar lista completa");
        puts("4 - Atualizar dados de paciente");
        puts("5 - Remover paciente");
        puts("-------------------------------");
        fgets(option,sizeof(option),stdin);

        if(option[0] > '5' || option[0] < '0'){
            puts("ERRO Digite uma opção válida!");
        }else if (option[1] >= '0'){
            puts("ERRO Digite uma opção válida!");
        }else{
            switch (option[0]){
            case '0':
                puts("Voltando ao Menu Principal...");
                return 0;
                break;
            case '1':
                puts("---------- Opção 1 ----------");
                teste(data);
                limpaBufferInput();
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
                break;
            }
        }
    }
}



#endif