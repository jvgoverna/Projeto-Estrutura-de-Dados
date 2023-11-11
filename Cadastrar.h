#ifndef CADASTRAR__H
#define CADASTRAR__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Data {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct Registro {
  char nome[20];
  int idade;
  char rg[11];
  Data entrada;
} Registro;

typedef struct Elista { //(Celula)
  Registro dados;
  struct Elista *anterior;
  struct Elista *proximo;
} Elista;

typedef struct Lista { //(LDE) ()
  Elista *inicio;
  int quantidade_Elmentos;
} Lista;

Lista *cria_lista(){
  Lista *lista = (Lista*)malloc(sizeof(Lista));
  lista->quantidade_Elmentos= 0;
  lista->inicio = NULL;
  return lista;
}

Elista *cria_Elista(Registro dados) {
  Elista *elista = (Elista *)malloc(sizeof(Elista));
  elista->dados = dados;
  elista->proximo = NULL;
  elista->anterior = NULL;
  return elista;
}

void inserir(Lista *lista, Registro dados) {
  Elista *novo = cria_Elista(dados);
  if(lista->quantidade_Elmentos>0){
    lista->inicio->anterior =novo;
    novo->proximo = lista->inicio;
  }
    lista->inicio = novo;
    lista->quantidade_Elmentos++;
}
void limpaBufferInput() {
  while (getchar() != '\n');
}

void escreverArquivo(Registro registro) {
  FILE *arquivo;

  arquivo = fopen("Cadastros.txt", "a"); // Abre em mode Append!
  // Escreve
  fprintf(arquivo, "Nome: %s", registro.nome);
  fprintf(arquivo, "RG: %s\n", registro.rg);
  fprintf(arquivo, "Idade: %d\n", registro.idade);
  fprintf(arquivo, "Dia: %d / Mes: %d / Ano: %d\n", registro.entrada.dia,
          registro.entrada.mes, registro.entrada.ano);
  fclose(arquivo); // Fecha automaticamente para escrever direto sem a
                   // neccesidade de encerrar o Prograam!
}

void escreverArquivobin(Registro registro) {
  FILE *arquivo;

  arquivo = fopen("CadastrosBin.txt", "ab"); // Abre em mode Append!
  // Escreve
  fwrite(&registro, sizeof(Registro), 1, arquivo);

  fclose(arquivo); // Fecha automaticamente para escrever direto sem a
                   // neccesidade de encerrar o Programa!
}

void leituraBin(Registro registro) {
  //passar todos os registros para a lista:
  FILE *arquivo;
  Lista *lista = cria_lista();
  arquivo = fopen("CadastrosBin.txt", "rb");
  if(arquivo == NULL){
    puts("ERRO! Arquivo vazio!");
    return;

  }
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {
    inserir(lista, registro);
  }
  fclose(arquivo);
  //mostrar a lista:
  Elista *atual = lista->inicio;
  if(atual==NULL){
    puts("Não há pessoas na lista");
  }
  while(atual!=NULL){
    printf("Nome = %s Rg = %s Idade = %d Data = %d/%d/%d\n", atual->dados.nome,
     atual->dados.rg, atual->dados.idade, atual->dados.entrada.dia,
     atual->dados.entrada.mes, atual->dados.entrada.ano);
    atual=atual->proximo;
  }
}

void consultarpaciente(Registro registro, char referencia[]) {
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
      printf("Nome = %s Rg = %s Idade = %d Data = %d/%d/%d\n", registro.nome, //printa a pessoa cadastrada
             registro.rg, registro.idade, registro.entrada.dia,
             registro.entrada.mes, registro.entrada.ano);

    }

  }
  if(verificador == 0){ //
    puts("Pessoa não foi cadastrada!");
  }
  fclose(arquivo);
}


void atualizarpaciente(Registro registro, char referencia2[]) {
  int verificador = 0;
  FILE *arquivo;
  FILE *arquivoparalelo;
  arquivo = fopen("CadastrosBin.txt", "rb");
  arquivoparalelo =  fopen("CadastrosBinparalelo.txt", "wb");

  if(arquivo == NULL){
    puts("ERRO! Arquivo vazio!");
    remove("CadastrosBinparalelo.txt");
    return;
  }
  //escrever o conteudo do arquivo para o paralelo
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) { //Lendo o conteúdo do arquivo
    if (strcmp(referencia2, registro.nome) == 0) { 
      verificador = 1;
      puts("Nova idade: ");
      scanf("%d", &registro.idade);
      puts("idade salva");
    }
      fwrite(&registro, sizeof(Registro), 1, arquivoparalelo);
  }
  if(verificador == 0){
    remove("CadastrosBinparalelo.txt");
    puts("Pessoa não Encontrada!");
    return;
  }
  fclose(arquivo);
  fclose(arquivoparalelo);
  remove("CadastrosBin.txt");
  rename("CadastrosBinparalelo.txt" , "CadastrosBin.txt");
  limpaBufferInput();
}

void removerpaciente(Registro registro, char referencia3[]) {
  FILE *arquivo;
  FILE *arquivoparalelo;
  int verificador = 0;
  arquivo = fopen("CadastrosBin.txt", "rb");
  arquivoparalelo =  fopen("CadastrosBinparalelodelete.txt", "wb");

  if (arquivo == NULL) {
    puts("ERRO! Arquivo vazio!");
    remove("CadastrosBinparalelodelete.txt");
    return;
  }

  // Escrever o conteudo do arquivo para o paralelo
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {
    if (strcmp(referencia3, registro.nome) != 0) {
      fwrite(&registro, sizeof(Registro), 1, arquivoparalelo);
    } else {
      verificador = 1;
      printf("Paciente %s foi deletado\n", registro.nome);
    }
  }

  if (verificador == 0) {
    puts("Pessoa não encontrada!");
    remove("CadastrosBinparalelodelete.txt");
    return;
  }

  fclose(arquivo);
  fclose(arquivoparalelo);

  remove("CadastrosBin.txt");
  rename("CadastrosBinparalelodelete.txt" , "CadastrosBin.txt");
  return;
}



void menuCadastrar() {
  Registro registro;
  char option[4];
  while (1) {
    puts("-------------------------------");
    puts("1 - Cadastrar novo paciente");
    puts("2 - Consultar paciente cadastrados");
    puts("3 - Mostrar lista completa");
    puts("4 - Atualizar dados de paciente");
    puts("5 - Remover paciente");
    puts("0 - Voltar ao menu principal");
    puts("-------------------------------");
    fgets(option, sizeof(option), stdin);
    if (option[0] > '5' || option[0] < '0') {
      puts("ERRO Digite uma opção válida!");
    } else if (option[1] >= '0') {
      puts("ERRO Digite uma opção válida!");
    } else {
      switch (option[0]) {
      case '0':
        puts("Voltando ao Menu Principal...");
        return;
        break;
      case '1':
        puts("---------- Opção 1 ----------");
        // Registro *registro = startRegistro();
        puts("Nome: ");
        int len_nome = sizeof(registro.nome);
        for (int i = 0; i < len_nome; i++) {
          if (registro.nome[i] == '\n') {
            registro.nome[i] = '\0';
          }
        }
        int len_Rg = sizeof(registro.rg);
        fgets(registro.nome, len_nome, stdin);
        int localvar = 0;
        while (1) {
          puts("RG: ");
          fgets(registro.rg, len_Rg, stdin);
          for (int i = 0; i < len_Rg; i++) {
            if (registro.rg[i] == '\n') {
              registro.rg[i] = '\0'; // Troca o \n pelo enter
              localvar = i;
            }
          }
          if (localvar == 9) { // Rg de 9 dígitos!!
            break;
          } else if (localvar != 9) {
            puts("ERRO!! Rg precisa ter 9 dígitos!");
          }
        }
        printf("Idade: ");
        scanf("%d", &registro.idade);
        while (1) {
          if (registro.idade <= 0 || registro.idade >= 120) {
            puts("ERRO Idade incorreta!");
            printf("Idade: ");
            scanf("%d", &registro.idade);
          } else {
            break;
          }
        }
        printf("Dia / Mês / Ano: ");
        scanf("%d %d %d", &registro.entrada.dia, &registro.entrada.mes,
              &registro.entrada.ano);
        escreverArquivo(registro);
        escreverArquivobin(registro);
        limpaBufferInput();
        break;
      case '2':
        puts("---------- Opção 2 ----------");
        char referencia[20];
        printf("Digite o nome do paciente cadastrado: ");
        fgets(referencia, sizeof(referencia), stdin);
        consultarpaciente(registro, referencia);
        break;
      case '3':
        puts("---------- Opção 3 ----------");
        leituraBin(registro);
        // imprimir_listacomp(lista);
        break;
      case '4':
        puts("---------- Opção 4 ----------");
        char referencia2[20];
        printf("Digite o nome do paciente cadastrado: ");
        fgets(referencia2, sizeof(referencia), stdin);
        atualizarpaciente(registro, referencia2);
        break;
      case '5':
        puts("---------- Opção 5 ----------");
        char referencia3[20];
        printf("Digite o nome do paciente cadastrado: ");
        fgets(referencia3, sizeof(referencia), stdin);
        removerpaciente(registro, referencia3);

        break;
      }
    }
  }
}

#endif