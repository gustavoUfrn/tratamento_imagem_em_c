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

void imprime_arquivo(int a, int l, Pixel pixels[a][l], Header header){
    int i, j;

    FILE * out_file;

    out_file = fopen("galinhos_rotatus.ppm", "wt");

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

void rotate(int a, int l, Pixel pixels[a][l], Header header){
    int i, j, temp=0;

    Pixel pixels_aux[l][a];

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            pixels_aux[j][a - 1 - i].red = pixels[i][j].red;
            pixels_aux[j][a - 1 - i].green = pixels[i][j].green;
            pixels_aux[j][a - 1 - i].blue = pixels[i][j].blue;
        }
    }

    temp = header.altura;
    header.altura = header.largura;
    header.largura = temp;

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

    rotate(header.altura, header.largura, pixels, header);

    return 0;
}