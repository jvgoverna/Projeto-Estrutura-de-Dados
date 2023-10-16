#include <stdio.h>
#include <ctype.h>




int main(){
    char option [100];
    while(1){
        printf("------------------------------\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar novo Paciente\n");
        printf("2 - Consultar paciente Cadastrado\n");
        printf("3 - Mostrar Lista Completa\n");
        printf("4 - Atualizar dados do Paciente\n");
        printf("5 - Remover Paciente\n");
        printf("------------------------------\n");

        fgets(option,sizeof(option),stdin);

        if(isdigit(option[0])){
            switch (option[0]){
                case '0':
                    puts("Saindo");
                    break;
                case '1':
                    puts("----- Opção 1 -----");
                    break;
                case '2':
                    puts("----- Opção 2 -----");
                    break;
                case '3':
                    puts("----- Opção 3 -----");
                    break;
                case '4':
                    puts("----- Opção 4 -----");
                    break;
                case '5':
                    puts("----- Opção 5 -----");
                    break;
                default:
                    printf("ERRO Digite um número válido!");
                    break;
            }
        }else{
            printf("ERRO Digite um número válido!");
        }
    }
    return 0;
}