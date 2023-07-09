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

    out_file = fopen("galilhos_blur.ppm", "wt");

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
void grayScale(int a, int l, Pixel pixels[a][l], Header header) {
    int media_red, media_green, media_blue;

    Pixel pixels_aux[a][l];

    for(int i=0; i<a; i++){
        for(int j=0; j<l; j++){
            if((i!=0 && j!=0) && (i!=a-1 && j!=l-1)){
                //Lógica para red
                media_red = (pixels[i-1][j-1].red + pixels[i-1][j].red + pixels[i-1][j+1].red +
                              pixels[i][j-1].red + pixels[i][j].red + pixels[i][j+1].red + 
                               pixels[i+1][j-1].red + pixels[i+1][j].red + pixels[i+1][j+1].red)/9;
                //Lógica para green
                media_green = (pixels[i-1][j-1].green + pixels[i-1][j].green + pixels[i-1][j+1].green +
                                pixels[i][j-1].green + pixels[i][j].green + pixels[i][j+1].green + 
                                 pixels[i+1][j-1].green + pixels[i+1][j].green + pixels[i+1][j+1].green)/9;
                //Lógica para blue
                media_blue = (pixels[i-1][j-1].blue + pixels[i-1][j].blue + pixels[i-1][j+1].blue +
                                pixels[i][j-1].blue + pixels[i][j].blue + pixels[i][j+1].blue + 
                                 pixels[i+1][j-1].blue + pixels[i+1][j].blue + pixels[i+1][j+1].blue)/9;
                          
                for(int o=i-1; o<a; o++){
                    for(int p=j-1; p<l; p++){
                        pixels_aux[o][p].red = media_red;
                        pixels_aux[o][p].green = media_green;
                        pixels_aux[o][p].blue = media_blue;
                    }
                }
            }
            media_red=0;
            media_green=0;
            media_blue=0;
        }
    }

    imprime_arquivo(header.altura, header.largura, pixels_aux, header);

    return;
}

// Função para imprimir arquivo final na pasta output
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