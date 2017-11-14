#include <stdlib.h>
#include <stdio.h>
#include "util.h"

typedef void (*Funcao)(void);

void manipula_imagem(void){
	imagem I = abrir_imagem(parametros.nome_imagem_base, parametros.brilho);
	salvar_imagem(parametros.nome_nova_imagem, &I);
}

void manipula_imagem_threads(void){
	imagem I = abrir_imagem_threads(parametros.nome_imagem_base, parametros.brilho,params.num_threads);
	salvar_imagem_threads(parametros.nome_nova_imagem, &I,params.num_threads);
}

void medir_tempo(Funcao func_analisada)
{
	func_analisada();
}


void run(void){

	printf("Nome da nova imegem: %s\n",parametros.nome_nova_imagem );
	printf("Brilho a ser aplicado: %.1f\n",parametros.brilho);
	printf("Numero de Threads: %d\n", params.num_threads);

	for (int i = 0; i< params.num_iteration; i++){
		switch (parametros.operacao){
			case ALTERA_BRILHO:
			case COPIA_IMAGEM:

				if(params.type == THREADS)
					medir_tempo(manipula_imagem_threads);
				else if (params.type == SEQUENCIAL)
					medir_tempo(manipula_imagem);
				break;

			case PIXEL_MAXIMO:

				if(params.type == THREADS)
					printf("Pixel max via thread\n");
				else if (params.type == SEQUENCIAL)
					printf("PIXEL_MAXIMO\n");
				break;

			default:
				printf("Erro!\n");
				exit(EXIT_FAILURE);
		}
	}


}



