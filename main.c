#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Mapa.h"

int main(){
    setlocale(LC_ALL,"portuguese");

    int ativo = 0;
    char nomeArquivo[300];
    FILE *arquivo;
    Mapa mapa;

    do{

        printf("*************************\n");
        printf("** RANKING DE PALAVRAS **\n");
        printf("*************************\n");

        printf("\n\nNome do arquivo de texto (Nao precisa colocar .txt): ");
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

            exibir_palavras(&mapa);

            libera_mapa(&mapa);

        }else{
            printf("Erro: arquivo não encontrado!\n");
        }

        printf("\nDeseja ler outro arquivo? [0-Não / 1-Sim]: ");
        scanf("%d",&ativo);

        if(ativo == 1){
            system("cls");
        }

    }while(ativo);

    return 0;
}
