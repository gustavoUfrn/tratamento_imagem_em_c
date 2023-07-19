// Bliblioteca padrões e Structs.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// Aloca uma matriz com base na altura e largura do Header
void MatrizPixels(ptn_header Header);

// Ler o arquivo com leitura padrão, cria um Header com os dados lidos e chama a MatrizPixels para fazer a primeria alocação da matriz de Pixels
void ler_arquivo(ptn_header Header);

// Ler o argumento passado na main e o retorna, também verifica se o argumento foi realmente passado
char* ler_argumentos(int pnt_int, char **pnt_char);

// Usa o valor retornado por ler_argumentos e compara esse valor com os valores de possiveis operações
// também é preciso passar Header, já que iremos utilizar-lo para chamar outras funcoes
void operacao(char* Operacao, ptn_header Header);

// gray: Cria uma nova imagem em escala de cinza;
void gray(ptn_header Header);

// rotate: Rotaciona a imagem 90° em sentido anit-hórario;
void rotate(ptn_header Header);

// blur: Cria uma nova imagem com a nitidez reduzida;
void blur(ptn_header Header);

// enlarge: Amplia a imagem em 2x;
void enlarge(ptn_header Header);

// reduce: Reduz a imagem em 2x;
void reduce(ptn_header Header);

// Imprime o arquivo final e libera a primeria alocação de header
void imprime_arquivo(ptn_header Header);
