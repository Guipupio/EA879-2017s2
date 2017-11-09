%{
#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#include <FreeImage.h>
#include <string.h>

void yyerror(char *c);
int yylex(void);
struct user_parameters params;


%}
%union {
  char    strval[50];
  int     ival;
  float   fval;
}
%token <strval> STRING MAX_PIXEL
%token <ival> VAR IGUAL EOL ASPA 
%token <fval> MULT Operacao
%left SOMA

%%

PROGRAMA:
	PROGRAMA OPERA_PIXEL EOL
	| PROGRAMA EXPRESSAO EOL
	| PROGRAMA PIXEL_MAXIMO EOL
	|
        ;


EXPRESSAO:
    | STRING IGUAL STRING {

    	if(params.type == 1){
	        // printf("Caso 1: Copiando %s para %s\n", $3, $1);
	        printf("Copia sequential\n");
	       	imagem I = abrir_imagem($3, 1.0);
			// printf("Li imagem %d por %d\n", I.width, I.height);
	        salvar_imagem($1, &I);
	    }else if (params.type == 2){
	    	 // printf("Caso 1: Copiando %s para %s\n", $3, $1);
	        printf("Copia com Threads\n");
	       	imagem I = abrir_imagem_threads($3, 1.0);
			// printf("Li imagem %d por %d\n", I.width, I.height);
	        salvar_imagem_threads($1, &I);

	    }
                          }

    ;

OPERA_PIXEL:

    | STRING IGUAL STRING Operacao {

		if(params.type == 1){
			// printf("Estamos passando o Float: %f\n", $4);
			// printf("Copiando %s para %s\n", $3, $1);
		    printf("Operando Brilho sequential\n");
		    imagem I = abrir_imagem($3, $4);
			printf("Li imagem %d por %d\n", I.width, I.height);
		    salvar_imagem($1, &I);
		} else if(params.type == 2){
			// printf("Estamos passando o Float: %f\n", $4);
			// printf("Copiando %s para %s\n", $3, $1);
		    printf("Operando Brilho com threads\n");
		    imagem I = abrir_imagem($3, $4);
			// printf("Li imagem %d por %d\n", I.width, I.height);
		    salvar_imagem($1, &I);
		}
				     }
    ;


PIXEL_MAXIMO:
    | MAX_PIXEL{
	
	printf("procurando pixel maximo...\n");
	printf("nome: %s\n", $1);
	float posicao[3];
	for (int i = 0; i<3 ; i++)	
		posicao[i] = 0.0;


	int *indice = pixel_max ($1, posicao);
	
	printf("A posicao onde o conjunto dos pixels sao maximos eh: %d\nLinha: %d\nColuna: %d\npixel RED: %.2f\npixel GREEN: %.2f\npixel BLUE: %.2f\n", indice[0],indice[1],indice[2], posicao[0],posicao[1],posicao[2]);

	
	
}
;





%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

void parse(int argc, char* argv[], struct user_parameters* params)
{
    int i;
    for(i=1; i<argc; i++) {
        if(!strcmp(argv[i], "-c"))
            params->check = 1;
        else if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            printf("----------------------------------------------\n");
            printf("-                Trabalho 2                  -\n");
            printf("-      Guia para parametros de execucao      -\n");
            printf("----------------------------------------------\n");
            printf("-h, --help : Show help information\n");
            printf("-c : Ask to check result\n");
            printf("-i : Number of iterations\n");
            printf("-n : Number of threads\n");
            printf("-t : Choose algorithm (leavng blank will run type task)\n(Options for type) 1 - sequential, 2 - with threads\n");
            exit(EXIT_SUCCESS);
        } else if(!strcmp(argv[i], "-i")) {
            if (++i < argc)
                params->num_iteration = atoi(argv[i]);
            else {
                fprintf(stderr, "-i requires a number\n");
                exit(EXIT_FAILURE);
            }
        } 
         else if(!strcmp(argv[i], "-n")) {
            if (++i < argc)
                params->num_threads = atoi(argv[i]);
            else {
                fprintf(stderr, "-n requires a number\n");
                exit(EXIT_FAILURE);
            }
        } else if(!strcmp(argv[i], "-t")) {
            if (++i < argc)
                params->type = atoi(argv[i]);
            else {
                fprintf(stderr, "-t requires a number\n");
                exit(EXIT_FAILURE);
            }
        } else
            fprintf(stderr, "Unknown parameter : %s\n", argv[i]);
    }
}

int main(int argc, char* argv[]) {

	memset(&params, 0, sizeof(params));
	params.type = 1; 		// default seq
	parse(argc, argv, &params);

	printf("Numero de Threads: %d\n", params.num_threads);
  FreeImage_Initialise(0);
  yyparse();

  

  return 0;

}
