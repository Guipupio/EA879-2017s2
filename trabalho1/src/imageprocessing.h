
#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H


typedef struct {
  unsigned int width, height;
  float *r, *g, *b;
} imagem;

typedef enum {
	COPIA_IMAGEM,
	ALTERA_BRILHO,
	PIXEL_MAXIMO
} casos;

typedef struct {
	casos operacao;
	char *primeiro_arquivo;
	char *segundo_arquivo;
	float brilho;
}user_parameters_operacao;


struct user_parameters {
	int type;		// type of execution
	int num_threads;	// number of threads
	int check;			// check result.
	int num_iteration;	// number of iteration
};

imagem abrir_imagem(char *nome_do_arquivo, float brilho);
void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *i);
int * pixel_max (char *nome_do_arquivo, float *posicao);

imagem abrir_imagem_threads(char *nome_do_arquivo, float brilho);
void salvar_imagem_threads(char *nome_do_arquivo, imagem *I);
void liberar_imagem_threads(imagem *i);
int * pixel_max_threads (char *nome_do_arquivo, float *posicao);

#endif
