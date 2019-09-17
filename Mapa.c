#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mapa.h"

#define TAM_BLOCO 10
#define ERRO_ALOC "Erro de alocação de memória\n"
#define ERRO_VAL "Valor Inválido!\n"
#define ERRO_VAZIA "Lista Vazia!\n"

void inicia_mapa(Mapa *map){

	*map = *((Mapa*) calloc(1,sizeof(Mapa)));

	if(map != NULL){

        map->lista = (Item**) calloc(TAM_BLOCO,sizeof(Item*));

        if(map->lista == NULL){
            printf(ERRO_ALOC);
            exit(1);
        }

        map->blocos = 1;
        map->total = 0;

	}else{
        printf(ERRO_ALOC);
        exit(1);
	}

}

void insere_termo(Mapa *mapa, char *s){

	if(mapa != NULL && s != NULL){

        int i,j,k;

        //Verifica se existe carcteres especiais
        char charEspeciais[7] = {'.',',',':',';','!','?'};

        j = (strlen(s)-1);
        for(i=0; i < 7; i++){
            if( s[j] == charEspeciais[i] ){
                s[j] = '\0';
            }
        }

        //Verifica se a palavra NÃO foi cadastrada
		if(incrementa(mapa,s) == 1){

			//Verifica se é necessário alocar mais um bloco
			if(mapa->total == (TAM_BLOCO * mapa->blocos) ){

                mapa->lista = (Item**) realloc(mapa->lista,
					(TAM_BLOCO * mapa->blocos + TAM_BLOCO) * sizeof(Item*) );

				if(mapa->lista != NULL){
					mapa->blocos++;
				}else{
					printf(ERRO_ALOC);
					exit(1);
				}

			}

			//Aloca palavra
            i = mapa->total;

			mapa->lista[i] = (Item*) malloc(sizeof(Item));

			if(mapa->lista[i] != NULL){

				mapa->lista[i]->termo = (char*) malloc(sizeof(s));

				if(mapa->lista[i]->termo != NULL){

                    mapa->total++;
					strcpy(mapa->lista[i]->termo,s);
					escreve_cont(mapa,mapa->lista[i]->termo,1);

				}else{
					printf(ERRO_ALOC);
					exit(1);
				}

			}else{
				printf(ERRO_ALOC);
				exit(1);
			}

		}else{//Se a palavra foi cadastrada então ordena
            //Ordena em ordem decrescente

            i=1;
            while(i < mapa->total){ //Descobre o item desordenado
                if(mapa->lista[i]->conta > mapa->lista[i-1]->conta){
                    break;
                }
                i++;
            }

            if(i != mapa->total){ //Se tiver o elemento desordenado

                Item *item = mapa->lista[i];//Reserva o elemento desordenado

                //Acha a posicao certa para colocar o elemento
                j = 0;
                while(j < mapa->total){
                    if(item->conta > mapa->lista[j]->conta){
                        break;
                    }
                    j++;
                }

                /*Deslocar os elementos acima da posição do elemento
                desordenado para uma posição abaixo até a posição onde o
                elemento vai ser colocado*/
                for(k=i; k > j; k--){
                    mapa->lista[k] = mapa->lista[k-1];
                }

                //Colocar o elemento no lugar certo
                mapa->lista[j] = item;

            }
		}

	}else{
		printf(ERRO_VAL);
	}

}

int incrementa(Mapa *mapa,char *s){

	if(mapa != NULL && s != NULL){ //Verifica se os valores são validos.

        //procura a existencia da palavra.
        if(mapa->total != 0){
            int i=0;
            while(i < mapa->total){

                if(strcasecmp(mapa->lista[i]->termo,s) == 0){ //iguais
                    escreve_cont(mapa,mapa->lista[i]->termo,
                        le_contador(mapa,mapa->lista[i]->termo) + 1);
                    break;
                }

                i++;
            }

            if(i != mapa->total){
                return 0; //Palavra já cadastrada.
            }
        }

		return 1; //Palavra não cadastrada ou não existe bloco ainda.
	}else{
		printf(ERRO_VAL);
		return -1; //Erro
	}

}

int escreve_cont(Mapa *mp, char *s, int c){

	if(mp != NULL && s != NULL && c >= 0){

        int i=0;
        while(i < mp->total){

            if(strcasecmp(mp->lista[i]->termo,s) == 0){ //iguais
                mp->lista[i]->conta = c;
                break;
            }

            i++;
        }

        if(i != mp->total){
            return 0; //Palavra encontrada
        }

		return 1; //Palavra não encontrada ou não existe bloco
	}else{
		printf(ERRO_VAL);
		return -1;
	}

}

int le_contador(Mapa *mp, char *s){

	if(mp != NULL && s != NULL){

        int i=0;
        while(i < mp->total){
            if(strcasecmp(mp->lista[i]->termo,s) == 0){ //iguais
                break;
            }
            i++;
        }

        if(i != mp->total){
            return mp->lista[i]->conta;
        }

        return 0; //Não existe bloco ou não encotrou a palavra
	}else{
		printf("Valores Invalidos\n");
		return -1; //Erro
	}

}

void remove_termo(Mapa *mp, char *s){

	if(mp != NULL && s != NULL){

		if(mp->total != 0){

            //Procura o termo s
			int i=0;
			while(i < mp->total){

                if(strcasecmp(mp->lista[i]->termo,s) == 0){
                    break;
                }

				i++;
			}

			if(i != mp->total){//Verifica se tem o termo

				Item *item = mp->lista[i]; //Reserva o item
				mp->lista[i] = NULL; //Declara nullo onde ele estava
				free(item->termo); //Libera o termo
				free(item); //Libera o item

                //Reorganiza os elementos na lista
				int j;
				for(j = i; j < mp->total; j++){
					mp->lista[j] = mp->lista[j+1];
				}

				mp->total--;

                //Verifica se precisa diminuir os blocos alocados
				if((mp->total == (mp->blocos * TAM_BLOCO - TAM_BLOCO)) && (mp->total != 0)){

					mp->lista = (Item**) realloc(mp->lista,
					((TAM_BLOCO * mp->blocos) - TAM_BLOCO) * sizeof(Item*));

					if(mp->lista == NULL){
						printf(ERRO_ALOC);
						exit(1);
					}

					mp->blocos--;

				}


			}else{
				printf("Palavra não encontrada!\n");
			}


		}else{
			printf(ERRO_VAZIA);
		}


	}else{
		printf(ERRO_VAL);
	}

}

void libera_mapa(Mapa *mp){

	if(mp != NULL){

		if(mp->lista != NULL){

			int i;
			for(i=0; i < (TAM_BLOCO * mp->blocos);i++){
				if(mp->lista[i] != NULL){
					free(mp->lista[i]->termo);
				}
				free(mp->lista[i]);
			}
            free(mp->lista);
		}

		free(mp);

	}

}

int tamanho_mapa(Mapa *mp){

	if(mp != NULL){

		if(mp->total != 0){
			return mp->total;
		}else{
			return 0; //Lista Vazia
		}

	}else{
		printf(ERRO_VAL);
		return -1;
	}

}

void le_termo(Mapa *mp, int i, char *t, int *c){

	if(mp != NULL && i >= 0){

		if(mp->lista != NULL){

			if(i < mp->total){

				strcpy(t,mp->lista[i]->termo);
				*c = mp->lista[i]->conta;

			}else{
				printf("Nao existe item no indice %d\n",i);
			}

		}else{
			printf(ERRO_VAZIA);
		}

	}else{
		printf(ERRO_VAL);
	}

}
