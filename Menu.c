#include <stdio.h>
#include "Sobre.c"
#include <ctype.h> //Biblioteca para dizer se um dado Byte representa um caractere alfanumérico ou não




int main(){
    char option [4];
    while(1){
        printf("------------------------------\n");
        printf("1 - Cadastrar novo Paciente\n");
        printf("2 - Consultar paciente Cadastrado\n");
        printf("3 - Mostrar Lista Completa\n");
        printf("4 - Atualizar dados do Paciente\n");
        printf("5 - Remover Paciente\n");
        printf("6 - Sobre\n");
        printf("7 - Sair\n");
        printf("------------------------------\n");

        fgets(option,sizeof(option),stdin);

        if(isdigit(option[0])){ //verifica se o primeiro caractere é um número
            if (ispunct(option[1])||option[1] >= '0'){ //verifica se o segundo caractere é um número ou um caractere de Pontuação
                printf("ERRO\n");
            }
            else{
            switch (option[0]){
                case '1':
                    puts("---------- Opção 1 ----------");
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
                case '6':
                    puts("---------- Opção 6 ----------");
                    sobre();
                    break;
                case '7':
                    puts("Saindo...");
                    return 0;
                    break;
                default:
                    puts("ERRO Digite uma opção válida!");
                    break;
            }
        }
        }
        else{ //se o primeiro caractere não for um número
            puts("ERRO Digite um número válido!");
        }
    }
    return 0;
}