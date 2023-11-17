//Includes utilizados
#include "Cadastrar.h"
#include "Atendimento.h"
#include "Pesquisa.h"
#include "Sobre.h"
#include "Limpar.h"
#include <stdio.h>

int main() {
  char option[4]; //Crio esse char option para receber a opção escolhida pelo usuário
  //e tratar erros caso o usuário não digite uma opção correta
  while (1) { //Crio um loop infinito para o menu
    puts("-------------------------------");
    puts("1 - Cadastrar");
    puts("2 - Atendimento");
    puts("3 - Pesquisa");
    puts("4 - Limpar Arquvivo");
    puts("5 - Sobre");
    puts("0 - Sair");
    puts("-------------------------------");
    fgets(option, sizeof(option), stdin); //Recebe a opção digitada pelo usuario

    //Tratamento de erros, caso aconteça erro o usuário deverá digitar novamente
    
    //Se o usuário digitar algo que tenha mais de um caractere
    //se o usuário digitar apenas caractere
    //Se o usuário digitar algo que não seja um número entre 0 a 5
    
    if (option[0] > '5' || option[0] < '0') {  
      puts("ERRO Digite uma opção válida!");
    } else if (option[1] >= '0') {
      puts("ERRO Digite uma opção válida!");
    } else {
      switch (option[0]) { //Switch case para cada opção
      case '0':
        puts("Saindo...");
        return 0;
        break;
      case '1':
        puts("---------- Opção 1 ----------");
        menuCadastrar();
        break;
      case '2':
        puts("---------- Opção 2 ----------");
        menuAtendimento();
        break;
      case '3':
        puts("---------- Opção 3 ----------");
        menuPesquisar();
        break;
      case '4':
        puts("---------- Opção 4 ----------");

        limpar();
        break;
      case '5':
        puts("---------- Opção 5 ----------");
        sobre();
        break;

        return 0;
      }
    }
  }
}