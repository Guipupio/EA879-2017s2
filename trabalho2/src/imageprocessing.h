
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
} _casos;

typedef enum{
	THREADS,
	SEQUENCIAL
} _type;

struct user_parameters_operacao {
	_casos operacao;
	char *nome_nova_imagem;
	char *nome_imagem_base;
	float brilho;
};


struct user_parameters {
	_type type;		// type of execution
	int num_threads;	// number of threads
	int type_image;	// check length.
	int num_iteration;	// number of iteration
};

imagem abrir_imagem(char *nome_do_arquivo, float brilho);
void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *i);
int * pixel_max (char *nome_do_arquivo, float *posicao);

imagem abrir_imagem_threads(char *nome_do_arquivo, float brilho, int num_threads);
void salvar_imagem_threads(char *nome_do_arquivo, imagem *I, int num_threads);
void liberar_imagem_threads(imagem *i);
int * pixel_max_threads (char *nome_do_arquivo, float *posicao, int num_threads);

extern struct user_parameters_operacao parametros;
extern struct user_parameters params;

#endif
