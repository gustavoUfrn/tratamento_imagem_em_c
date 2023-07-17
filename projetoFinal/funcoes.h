// Funções.h além de ter a chamada de blibliotecas da linguagem, 
// Também vai ter a biblioteca de tipos que foi criada pelo desenvolvedor (structs.h)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// Cria uma matriz com alocação dinamica baseada na altura e largura da imagem, 
// Além de usar o tamanho de Pixel( Comtém 3 inteiros red, green, blue)
void MatrizPixels(ptn_header Header);

// Lê o arquivo de imagem tipo p3
void lerImagem(ptn_header Header);

// Lê os argumentos passados pelo usuário
char* lerArgumentos(int pnt_int, char **pnt_char);

// Faz a operação/funcao com base no que o usuário escolheu
void operacao(char* Operacao, ptn_header Header);

// Funcao criada para aplicar o efeito de escala cinza
void grayScale(ptn_header Header);

// Funcao criada para aplicar o efeito blur na imagem
void blur(ptn_header Header);

// Funcao criada para ampliar a imagem em 2x
void ampliar(ptn_header Header);

// Funcao criada para reduzir a imagem em 2x
void reduzir(ptn_header Header);

// Imprime a imagem final
void imprime_arquivo(char* Operacao, ptn_header Header);


