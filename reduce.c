#include <stdio.h>
#include <math.h>
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

void imprime_arquivo(int a, int l, Pixel pixels[a][l], Header header){
    int i, j;

    FILE * out_file;

    out_file = fopen("galilhos_red.ppm", "wt");

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

// Transformação de imagem para escala de cinza
void reduce(int a, int l, Pixel pixels[a][l], Header header) {
    Pixel pixels_aux[a/2][l/2];

    header.altura = a/2;
    header.largura = l/2;

    for(int i=0; i< header.altura; i++){
        for(int j=0; j<header.largura; j++){
            pixels_aux[i][j].red = (pixels[i*2][j*2].red + pixels[i*2+1][j*2].red + pixels[i*2][j*2+1].red + pixels[i*2+1][j*2+1].red)/4;
            pixels_aux[i][j].green = (pixels[i*2][j*2].green + pixels[i*2+1][j*2].green + pixels[i*2][j*2+1].green + pixels[i*2+1][j*2+1].green)/4;
            pixels_aux[i][j].blue = (pixels[i*2][j*2].blue + pixels[i*2+1][j*2].blue + pixels[i*2][j*2+1].blue + pixels[i*2+1][j*2+1].blue)/4;
        }
    }

    imprime_arquivo(header.altura, header.largura, pixels_aux, header);

    return;
}

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

    reduce(header.altura, header.largura, pixels, header);

    return 0;
}