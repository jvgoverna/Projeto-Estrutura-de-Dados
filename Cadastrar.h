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

void teste(Data *data){
    puts("Dia");
    scanf("%d", &data->dia);
    puts("Mes");
    scanf("%d", &data->mes);
    puts ("Ano");
    scanf("%d", &data->ano);
    printf("Dia %d Mes %d Ano %d\n", data->dia, data->mes, data->ano);
}

#endif