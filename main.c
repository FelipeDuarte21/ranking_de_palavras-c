#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Mapa.h"
#define ERRO_ARQUIVO "Nenhum arquivo informado! Vá para a opção 1\n"

char nomeArquivo[300];
Mapa mapa;

void exibir(Mapa *mapa){

    int i,j,k;

    printf("\n");
    for(i=0; i < 40; i++){
        printf("-");
    }

    printf("\n");
    printf("| TOTAL DE PALAVRAS: %-17d |\n",mapa->total);
    for(i=0; i < 40; i++){
        printf("-");
    }
    printf("\n");

    printf("|%4s PALAVRA %5s|%4s QUANTIDADE %3s|\n","","","","");

    for(i=0; i < mapa->total; i++){
        for(j=0; j < 40; j++){
            printf("-");
        }
        printf("\n");

        strupr(mapa->lista[i]->termo);
        printf("|%s", mapa->lista[i]->termo);
        j = 18 - strlen(mapa->lista[i]->termo);
        for(k=0; k < j; k++){
            printf("%1s","");
        }
        printf("|%10d%10s\n",mapa->lista[i]->conta,"|");
    }

    for(i=0; i < 40; i++){
        printf("-");
    }
    printf("\n");

}

void opcao1(){

    FILE *arquivo;

    system("cls");
    printf("1 - Ler arquivo\n");
    printf("Digite o caminho (não precisa colocar txt)\n>:");
    scanf("%s",nomeArquivo);

    strcat(nomeArquivo,".txt");
    arquivo = fopen(nomeArquivo,"r");

    if(arquivo != NULL){

        inicia_mapa(&mapa);

        char p[50];
        while(fscanf(arquivo,"%s ",p) != EOF){
            strcat(p,"\0");
            insere_termo(&mapa,p);
            strcpy(p,"");
        }

        fclose(arquivo);

        exibir(&mapa);

    }else{
        strcpy(nomeArquivo,"");
        nomeArquivo[0] = '\0';
        printf("Erro: arquivo não encontrado!\n");
    }

}

void opcao2(){
    system("cls");
    printf("2 - Ranking Completo\n\n");
    printf("Arquivo: %s\n",nomeArquivo);

    if(nomeArquivo[0] != '\0'){
        exibir(&mapa);
    }else{
        printf(ERRO_ARQUIVO);
    }
}

void opcao3(){
    system("cls");
    printf("3 - Intervalo de Ranking\n");

    if(nomeArquivo[0] != '\0'){
        int min,max;

        printf("Digite a qtd Max:\n>:");
        scanf("%d",&max);
        printf("Digite a qtd Min:\n>:");
        scanf("%d",&min);
        printf("Arquivo: %s\n",nomeArquivo);

        Mapa mapaAuxiliar;
        inicia_mapa(&mapaAuxiliar);

        int i;
        for(i=0; i < mapa.total; i++){
            if(mapa.lista[i]->conta >= min && mapa.lista[i]->conta <= max){
                insere_termo(&mapaAuxiliar,mapa.lista[i]->termo);
                escreve_cont(&mapaAuxiliar,mapa.lista[i]->termo,mapa.lista[i]->conta);
            }
        }

        exibir(&mapaAuxiliar);
    }else{
        printf(ERRO_ARQUIVO);
    }

}

void opcao4(){
    system("cls");
    printf("4 - Buscar Palavra\n");

    if(nomeArquivo[0] != '\0'){

        int fim;
        char palavra[50];

        do{
            printf("Digite a palavra ou '0' para voltar ao menu.\n>:");
            scanf("%s",palavra);

            fim = strcasecmp(palavra,"0");

            if(fim != 0){
                printf("Quantidade: %d\n",le_contador(&mapa,palavra));
            }

        }while(fim != 0);


    }else{
        printf(ERRO_ARQUIVO);
    }
}

void opcao5(){
    system("cls");
    printf("5 - Opções\n");

    if(nomeArquivo[0] != '\0'){

        int caracteres;
        printf("Digite o mínimo de caracteres a considerar\n>:");
        scanf("%d",&caracteres);

        Mapa mapaAuxiliar;
        inicia_mapa(&mapaAuxiliar);

        int i;
        for(i=0; i < mapa.total; i++){
            if(strlen(mapa.lista[i]->termo) >= caracteres){
                insere_termo(&mapaAuxiliar,mapa.lista[i]->termo);
                escreve_cont(&mapaAuxiliar,mapa.lista[i]->termo,mapa.lista[i]->conta);
            }
        }

        exibir(&mapaAuxiliar);

    }else{
        printf(ERRO_ARQUIVO);
    }

}

void menu(int opcao){

    switch(opcao){
        case 1:
            opcao1();
            break;
        case 2:
            opcao2();
            break;
        case 3:
            opcao3();
            break;
        case 4:
            opcao4();
            break;
        case 5:
            opcao5();
            break;
        case 6:
            break;
        default:
            printf("Valor Inválido!\n");
            break;
    }
}

int main(){
    setlocale(LC_ALL,"portuguese");

    nomeArquivo[0] = '\0';
    int acao = 0;

    do{
        printf("\n");
        printf("*************************\n");
        printf("** RANKING DE PALAVRAS **\n");
        printf("*************************\n");

        printf("Menu:\n");
        printf("1 - Ler arquivo txt\n");
        printf("2 - Exibir ranking completo\n");
        printf("3 - Exibir intervalo de ranking\n");
        printf("4 - Buscar Palavra\n");
        printf("5 - Opções\n");
        printf("6 - Sair\n");
        printf("ação: ");
        scanf("%d",&acao);

        menu(acao);

    }while(acao!=6);

    libera_mapa(&mapa);

    return 0;
}
