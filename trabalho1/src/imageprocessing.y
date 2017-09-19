%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>
#include <string.h>

void yyerror(char *c);
int yylex(void);



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
        printf("Caso 1: Copiando %s para %s\n", $3, $1);
       	imagem I = abrir_imagem($3, 1.0);
	printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);

                          }

    ;

OPERA_PIXEL:

    | STRING IGUAL STRING Operacao {

	printf("Estamos passando o Float: %f\n", $4);
	printf("Copiando %s para %s\n", $3, $1);
       	imagem I = abrir_imagem($3, $4);
	printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
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

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
