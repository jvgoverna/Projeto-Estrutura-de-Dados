#ifndef CADASTRAR__H
#define CADASTRAR__H
#include <stdio.h>
#include <stdlib.h>




typedef struct Data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Registro {
    char nome[20];
    int idade;
    char rg[11];
    Data entrada;
} Registro;

typedef struct Elista{  //(Celula)
  Registro dados;
  struct Elista *proximo;
}Elista;

typedef struct Lista{ //(LDE)
  Elista *inicio;
  int quantidade_Elmentos; 
}Lista;


Lista *cria_lista(){
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->quantidade_Elmentos = 0;
    return lista;
}

Elista *cria_Elista(Registro dados){
    Elista *elista = (Elista*) malloc(sizeof(Elista));
    elista ->dados = dados;
    elista ->proximo = NULL;
    return elista;
}

void inserir(Lista *lista, Registro dados){
   /* if(verifica_repeticao(lista,dados)){
        printf("Pessoa ja foi inserida!\n");
        return;
    }*/
    Elista *nova = cria_Elista(dados); //Cria a Elista recebendo os dados de um Struct!
    if(lista ->inicio == NULL){
        lista -> inicio = nova;
    }else{
        Elista *atual = lista -> inicio; //Começa desde o primeiro valor!
        Elista *anterior = NULL; //Tambem
        while (atual != NULL){
            anterior = atual;
            atual = atual -> proximo;

        }
        if(anterior == NULL){ //Se o anterior for NULL, significa que o valor é menor que o primeiro elemento da lista, logo, o novo elemento será o primeiro da lista.
            nova -> proximo = atual;//o proximo elemento apartir da nova celula aponta para o primeiro elemento da lista.
            lista ->inicio = nova;//O primeiro elemento da lista recebe a nova celula.

        }else{
            if(atual == NULL){ //Significa que o valor é maior que todos os elementos da lista, logo, o novo elemento será o ultimo da lista.
                anterior -> proximo = nova;
            }else{//Siginifica que o valor é maior que o anterior e menor que o proximo
                nova -> proximo = atual;
                anterior -> proximo = nova;
            }
        }
    }
    lista -> quantidade_Elmentos++;
}



void limpaBufferInput(){
    while(getchar() != '\n'); 
}

void procurarNome(Lista* lista, char nome[]) {
    printf("%s", nome);
    int control = 0;
    Elista* atual = lista->inicio;
    if(lista->quantidade_Elmentos == 0){
      //quando não há nome ou pacientes na lista
      control = 1;
    }
    while(atual != NULL) { //Enquanto a lista não chegar ao final!
      for (int i = 0; nome[i] != '\0'; i++) { //percorre a lista até achar o enter
          if(nome[i] != atual->dados.nome[i]) { //se o nome for diferente!
            control = 1;
            break;
          }
      }
      atual = atual->proximo;
    }
      if(control == 0){
          puts("Paciente encontrado!");
      }else if(control == 1){
        puts("Paciente não encontrado!");
      }
}
void imprimir_listacomp(Lista* lista) {
    Elista* atual = lista->inicio;
    printf("Total de Pessoas Cadastradas: %d pessoas\n", lista->quantidade_Elmentos);
    while (atual != NULL) {
        printf("Nome: %s", atual->dados.nome);
        printf("Rg: %s \n", atual->dados.rg);
        printf("Idade: %d \n", atual->dados.idade);
        printf("\n");
        atual = atual->proximo;
    }
  printf("\n");
}

 
void menuCadastrar(){
    //iniciar arquivo 
    //FILE *Arquivo;
    //Arquivo = fopen ("infos.txt","a");

    //if (Arquivo == NULL) {
     //printf("\nArquivo não pode ser aberto");
     //}

    
    Lista *lista = cria_lista();
    Registro registro;
    char option[4];
    while(1){
        puts("-------------------------------");
        puts("1 - Cadastrar novo paciente");
        puts("2 - Consultar paciente cadastrados");
        puts("3 - Mostrar lista completa");
        puts("4 - Atualizar dados de paciente");
        puts("5 - Remover paciente");
        puts("0 - Voltar ao menu principal");
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
                return;
                break;
            case '1':
              puts("---------- Opção 1 ----------");
              //Registro *registro = startRegistro();
              puts("Nome: ");
              int len_nome = sizeof(registro.nome);
              for(int i = 0 ; i < len_nome;i++){
                if(registro.nome[i] == '\n'){
                  registro.nome[i] = '\0';
                }
              }
              int len_Rg = sizeof(registro.rg);
              fgets(registro.nome, len_nome,stdin);
              int localvar = 0;
              while(1){
                puts("RG: ");
                fgets(registro.rg, len_Rg, stdin);
                for(int i = 0; i < len_Rg; i++){
                  if(registro.rg[i] == '\n'){
                    registro.rg[i] = '\0'; //Troca o \n pelo enter 
                    localvar =i;
                  }
                }
                if(localvar == 9){ //Rg de 9 dígitos!!
                  break;
                }
                else if(localvar != 9 ){
                  puts("ERRO!! Rg precisa ter 9 dígitos!");
                  }
              }
              

/*                for(int i = 0; i < sizeof(registro.rg); i++){
                if(registro.rg[i] >= 'a' && registro.rg[i] <= 'z' && registro.rg[i] >= 'A' && registro.rg[i] <= 'Z'){
                  printf("ERRO");
                  fgets(registro.rg, len_Rg, stdin); 

                }
              }*/
              //getchar();
              printf("Idade: ");
              scanf("%d", &registro.idade);
              printf("Dia / Mês / Ano: ");
              scanf("%d %d %d", &registro.entrada.dia, &registro.entrada.mes, &registro.entrada.ano);
              inserir(lista, registro);
              limpaBufferInput();
              break;
                break;
            case '2':
                puts("---------- Opção 2 ----------");
                char referencia[20];
                printf("Digite o nome do paciente cadastrado: ");
                fgets(referencia, sizeof(referencia), stdin);
                procurarNome(lista, referencia);
                break;
            case '3':
                puts("---------- Opção 3 ----------");
                imprimir_listacomp(lista);
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