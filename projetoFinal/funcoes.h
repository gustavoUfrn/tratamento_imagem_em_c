#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void MatrizPixels(ptn_header Header);

void ler_arquivo(ptn_header Header);

char* lerArgumentos(int pnt_int, char **pnt_char);

void operacao(char* Operacao, ptn_header Header);

void grayScale(ptn_header Header);

void rotate(ptn_header Header);

void blur(ptn_header Header);

void ampliar(ptn_header Header);

void reduzir(ptn_header Header);

void imprime_arquivo(ptn_header Header);


