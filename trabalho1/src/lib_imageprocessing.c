
#include <stdlib.h>
#include <stdio.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

imagem abrir_imagem(char *nome_do_arquivo, float brilho) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed*brilho < 255 ? color.rgbRed*brilho : 255;
      I.g[idx] = color.rgbGreen*brilho < 255 ? color.rgbGreen*brilho : 255;
      I.b[idx] = color.rgbBlue*brilho < 255 ? color.rgbBlue*brilho : 255;
    }
   }
  return I;

}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}

int pixel_max (char *nome_do_arquivo, float *posicao){
FIBITMAP *bitmapIn;
  int x, y, indice_max;
  float aux1[3];
  RGBQUAD color;
  imagem I;
	
 //

	for (int i = 0; i<3; i++){
		posicao[i] = 0.0;	
		aux1[i] = 0.0;
	}

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      float soma_aux = 0.0, soma = 0.0;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;

	aux1[0] = I.r[idx];
	aux1[1] = I.g[idx];
	aux1[2] = I.b[idx];
	
	//printf("Imagem: %.2f\n", I.r[idx]);
	for (int k = 0; k<3 ; k++){
		soma_aux += aux1[k]; 	
		soma +=	posicao[k];
		//printf("Aux1[k] =  %.2f\nsoma: %.2f\n",aux1[k], soma_aux);
	}
	if (soma_aux > soma){
		indice_max = idx;
		for (int k = 0; k<3 ; k++)
			posicao[k] = aux1[k];
	} 
	

	
	
     }	

 
    }

return indice_max;
  }

	




