#include <stdio.h>
#include <stdlib.h>

// Definição de tipo para o arquivo
typedef struct {
    char tipo_p[10];
    int altura;
    int largura;
    int tam_rgb;
} Header;

// Definição de tipo para os pixels
typedef struct {
    int red;
    int green;
    int blue;
} Pixel;

// Transformação de imagem para escala de cinza
void grayScale(int a, int l, Pixel pixels[a][l], Header header) {
    int i, j;

    for(i=0; i<a; i++){
        for(j=0; j<l; j++){
            int gray_value = 0;
            gray_value = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue)/3;
            pixels[i][j].red = gray_value;
            pixels[i][j].green = gray_value;
            pixels[i][j].blue = gray_value;
        }
    }

    imprime_arquivo(header.altura, header.largura, pixels, header);

    return;
}

// Função para imprimir arquivo final na pasta output
void imprime_arquivo(int a, int l, Pixel pixels[a][l], Header header){
    int i, j;

    FILE * out_file;

    out_file = fopen("galilhos_gray.ppm", "wt");

    if(out_file == NULL){
        printf("Erro ao abrir o arquivo!");
    } else {
        fprintf(out_file, "%s\n", header.tipo_p);
        fprintf(out_file, "%d %d\n", header.largura, header.altura);
        fprintf(out_file, "%d\n", header.tam_rgb);
    }

    for(i=0; i<header.altura; i++){
        for(j=0; j<header.largura; j++){
            fprintf(out_file, "%3d %3d %3d ", pixels[i][j].red, pixels[i][j].green, pixels[i][j].blue);
        }
        fprintf(out_file, "\n");
    }

    fclose(out_file);

    return;
}

// Função main, atualmente está preenchida com a leitura do arquivo, declaração de alguns tipos
// Funções atuais: Chamar função para gerar arquivo final e função para transformação em escala de cinza
int main(){
    int i, j;

    FILE *arquivo;

    arquivo = fopen("galinhos.ppm", "rt");

    if(arquivo == NULL){
        printf("Erro ao ler arquivo!\n");
    }

    Header header;

    fscanf(arquivo, "%s\n", header.tipo_p);
    fscanf(arquivo, "%d %d\n", &header.largura, &header.altura);
    fscanf(arquivo, "%d\n", &header.tam_rgb);

    Pixel pixels[header.altura][header.largura];

    // Leitura da matriz que está no arquivo de acordo com altura e largura.
    for(i=0; i<header.altura; i++){
        for(j=0; j<header.largura; j++){
            fscanf(arquivo, "%d %d %d", &pixels[i][j].red, &pixels[i][j].green, &pixels[i][j].blue);
        }
    }

    fclose(arquivo);

    grayScale(header.altura, header.largura, pixels, header);

    return 0;
}