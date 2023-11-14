#ifndef LIMPAR__H
#define LIMPAR__H
#include <stdio.h>
#include <stdlib.h>
#include "Cadastrar.h"


void limpar(){
  limparTela();
  remove("CadastrosBin.txt");
  remove("Cadastros.txt");
  puts("Limpando Arquivo...");
}

#endif