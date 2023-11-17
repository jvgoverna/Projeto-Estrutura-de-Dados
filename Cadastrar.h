#ifndef CADASTRAR__H //includes utilizados
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

typedef struct Lista { //(LDE)
  Elista *inicio;
  int quantidade_Elmentos;
} Lista;

Lista *cria_lista(){ //crio a lista
  Lista *lista = (Lista*)malloc(sizeof(Lista)); //Reservo um espaço na memória para armazenar a lista
  
  lista->quantidade_Elmentos= 0; //seta a quantidade para 0
  lista->inicio = NULL; //seto o início da lista para null, ou seja está vazia
  return lista;
}
//inicializa a LDE
Elista *cria_Elista(Registro dados) {
  Elista *elista = (Elista *)malloc(sizeof(Elista));//Reservo um espaço na memória para armazenar a Elista
  elista->dados = dados; //seto o item do struct da Elista (dados) para receber o registro
  elista->proximo = NULL; //seto o proximo para null, (não há)
  elista->anterior = NULL; //seto o anterior para null
  return elista;
}

void inserir(Lista *lista, Registro dados) { //função de inserir na lista
  Elista *novo = cria_Elista(dados); //crio uma nova elista
  if(lista->quantidade_Elmentos>0){ //se não tiver nada na lista
    lista->inicio->anterior =novo; //o ponteiro anterior do elemento inicio da lista aponta para o elemento novo recém-criado. 
    novo->proximo = lista->inicio; //o ponteiro "próximo" da elista aponta para o ponteiro "inicio" da lista
  }
    lista->inicio = novo; //o inicio da lista aponta para o novo
    lista->quantidade_Elmentos++; //aumenta a quantidade de elementos
}
void limpaBufferInput() { //função para limpar o buffer do stdin
  while (getchar() != '\n');
}


void escreverArquivobin(Registro registro) { //escreve todos os usuários cadastrados em um arquivo binário
  FILE *arquivo; 

  arquivo = fopen("CadastrosBin.txt", "ab"); // Abre em mode Append!
  // Escreve tudo oq está do struct do registro (cadastrados)
  fwrite(&registro, sizeof(Registro), 1, arquivo);

  fclose(arquivo); // Fecha automaticamente para escrever direto sem a
                   // neccesidade de encerrar o Programa!
}

void leituraBin(Registro registro) { //ler o arquivo binário
  //passar todos os registros para a lista:
  FILE *arquivo;
  Lista *lista = cria_lista(); //cria a lista
  arquivo = fopen("CadastrosBin.txt", "rb"); 
  if(arquivo == NULL){ //arquivo não vazio
    puts("ERRO! Arquivo vazio!");
    return;

  }
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {// fazer  a leitura do txt onde armazena o registro
    inserir(lista, registro); //insere cada registro na LDE
  }
  fclose(arquivo);
  //mostrar a lista:
  
  Elista *atual = lista->inicio; //crio uma ramificação da Elista para poder printar todos os cadastrados
  if(atual==NULL){
    puts("Não há pessoas na lista");
  }
  //percorre a LDE para printar todos os cadastrados
  while(atual!=NULL){
    printf("Nome = %s Rg = %s Idade = %d Data = %d/%d/%d\n", atual->dados.nome,
     atual->dados.rg, atual->dados.idade, atual->dados.entrada.dia,
     atual->dados.entrada.mes, atual->dados.entrada.ano);
    atual=atual->proximo;
  }
}

void consultarpaciente(Registro registro, char referencia[]) { //função achar o paciente cadastrado
  int verificador = 0;
  FILE *arquivo;
  arquivo = fopen("CadastrosBin.txt", "rb"); 
  if(arquivo == NULL){
    puts("ERRO! Arquivo vazio!");
    return;
  }
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) { //percorre o arquivo
    if (strcmp(referencia, registro.nome) == 0) { //Se o Nome que pesquisar for igual ao escrito no arquivo retorna 0, oq quer dizer que é igual!
      verificador = 1; //encontrou a pessoa!
      printf("Nome = %s Rg = %s Idade = %d Data = %d/%d/%d\n", registro.nome, //printa a pessoa cadastrada
             registro.rg, registro.idade, registro.entrada.dia,
             registro.entrada.mes, registro.entrada.ano);

    }

  }
  if(verificador == 0){ //nome pesquisado não é igual ao cadastrado
    puts("Pessoa não foi cadastrada!");
  }
  fclose(arquivo);
}


void atualizarpaciente(Registro registro, char referencia2[]) { //atualiza a idade do paciente
  int verificador = 0;
  FILE *arquivo;
  FILE *arquivoparalelo; //cria outro arquivo abre os dois sendo um em modo de leitura e outro em escrita
  //o arquivo paralelo será responsável em passar as informações ATUALIZADAS dos cadastrados para o paralelo, depois o nome é trocado novamente para cadastros
  arquivo = fopen("CadastrosBin.txt", "rb"); 
  arquivoparalelo =  fopen("CadastrosBinparalelo.txt", "wb");

  if(arquivo == NULL){ //se não tiver nenhum cadastro
    puts("ERRO! Arquivo vazio!"); 
    remove("CadastrosBinparalelo.txt"); //não faz nada apenas remove o paralelo
    return;
  }
  //escrever o conteudo do arquivo para o paralelo
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) { //Lendo o conteúdo do arquivo
    if (strcmp(referencia2, registro.nome) == 0) {//Se o Nome que pesquisar for igual ao escrito no arquivo retorna 0, oq quer dizer que é igual!
      verificador = 1;
      puts("Nova idade: "); 
      scanf("%d", &registro.idade); //pergunta a nova idade do usuário
      puts("idade salva"); 
    }
      fwrite(&registro, sizeof(Registro), 1, arquivoparalelo); //salva a idade atualizada da Pessoa no paralelo
  }
  if(verificador == 0){ //se o nome digitado não for igual ao da pessoa há pessoa não vai ser encontrada
    remove("CadastrosBinparalelo.txt");
    puts("Pessoa não Encontrada!");
    return;
  }
  fclose(arquivo); //fecha os dois arquivos remove o CadatrosBin (que é o arquivo desatualizado) e renomea o paralelo para dar a impressão que é o mesmo arquivo
  fclose(arquivoparalelo);
  remove("CadastrosBin.txt");
  rename("CadastrosBinparalelo.txt" , "CadastrosBin.txt");
  limpaBufferInput(); //limpa o buffer do input
}

void removerpaciente(Registro registro, char referencia3[]) {
  FILE *arquivo;
  FILE *arquivoparalelo;
  int verificador = 0;
  arquivo = fopen("CadastrosBin.txt", "rb"); //mesma lógica do atualizar só que agora é o de remoção
  arquivoparalelo =  fopen("CadastrosBinparalelodelete.txt", "wb");

  if (arquivo == NULL) { //abre o arquivo se não estiver vazio
    puts("ERRO! Arquivo vazio!");
    remove("CadastrosBinparalelodelete.txt");
    return;
  }

  // Escrever o conteudo do arquivo para o paralelo
  while (fread(&registro, sizeof(struct Registro), 1, arquivo)) {
    if (strcmp(referencia3, registro.nome) != 0) { 
      fwrite(&registro, sizeof(Registro), 1, arquivoparalelo); 
    } else { //deleta
      verificador = 1;
      printf("Paciente %s foi deletado\n", registro.nome);
    }
  }

  if (verificador == 0) { //se não encontrar
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

void limparTela() { //limpa a tela do terminal
  system("cls||clear");
}

void menuCadastrar() { //menu cadastrar mesma lógica de verificar se o usuário digitou corretamente
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
      limparTela();
      puts("ERRO Digite uma opção válida!");
    } else if (option[1] >= '0') {
      limparTela();
      puts("ERRO Digite uma opção válida!");
    } else {
      switch (option[0]) {
      case '0':
        limparTela();
        puts("Voltando ao Menu Principal...");
        return;
        break;
      case '1':
        puts("---------- Opção 1 ----------");
        limparTela();
        // Registro *registro = startRegistro();
        puts("Nome: "); //pergunta o nome e remove o \n no final da string para o \0(enter)
        int len_nome = sizeof(registro.nome);
        for (int i = 0; i < len_nome; i++) {
          if (registro.nome[i] == '\n') {
            registro.nome[i] = '\0';
          }
        }
        int len_Rg = sizeof(registro.rg);
        fgets(registro.nome, len_nome, stdin);
        int localvar = 0;
        while (1) { //lógica para que se o usuário digitar um RG com menos de 9 dígitos ele ficar perguntando até digitar 9 dígitos
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
        printf("Idade: "); //pergunta a idade sendo que o usuário deve ter mais que 0 anos e menos que 120
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
        printf("Dia / Mês / Ano: "); //pergunta o dia
        scanf("%d %d %d", &registro.entrada.dia, &registro.entrada.mes,
              &registro.entrada.ano);
        escreverArquivobin(registro); //escreve tudo isso no arquivo binário
        limpaBufferInput(); //limpa o buffer do input
        break;
      case '2':
        puts("---------- Opção 2 ----------");
        limparTela();
        char referencia[20];
        printf("Digite o nome do paciente cadastrado: ");
        fgets(referencia, sizeof(referencia), stdin); //controle para ver se o nome está no arquivo
        consultarpaciente(registro, referencia); //função de consultar
        break;
      case '3':
        puts("---------- Opção 3 ----------");
        limparTela();
        leituraBin(registro); //ler o arquivo e printa os cadastrados
        // imprimir_listacomp(lista);
        break;
      case '4':
        puts("---------- Opção 4 ----------");
        limparTela();
        char referencia2[20];
        printf("Digite o nome do paciente cadastrado: ");
        fgets(referencia2, sizeof(referencia), stdin); //controle para ver se o nome está no arquivo
        atualizarpaciente(registro, referencia2); //função de atualizar a idade do paciente
        break;
      case '5':
        puts("---------- Opção 5 ----------");
        limparTela();
        char referencia3[20];
        printf("Digite o nome do paciente cadastrado: ");
        fgets(referencia3, sizeof(referencia), stdin); //controle para ver se o nome está no arquivo
        removerpaciente(registro, referencia3); //remove o paciente

        break;
      }
    }
  }
}

#endif