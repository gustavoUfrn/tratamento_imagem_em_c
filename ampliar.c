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

// Função para imprimir arquivo final na pasta output
void imprime_arquivo(int a, int l, Pixel pixels[a][l], Header header){
    int i, j;

    FILE * out_file;

    out_file = fopen("galinhos_amp.ppm", "wt");

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
void ampliar(int a, int l, Pixel pixels[a][l], Header header) {
    int a_amp = a + (a-1);
    int l_amp = l + (l-1);

    header.altura = a_amp;
    header.largura = l_amp;

    Pixel pixels_aux[a_amp][l_amp];

    for (int i = 0; i < a_amp; i++){
        for (int j = 0; j < l_amp; j++){
            pixels_aux[i][j].red = 0;
            pixels_aux[i][j].green = 0;
            pixels_aux[i][j].blue = 0;
        }
    }

    for (int i = 0; i < a; i++){
        for (int j = 0; j < l; j++){
            pixels_aux[i*2][j*2].red = pixels[i][j].red;
            pixels_aux[i*2][j*2].green = pixels[i][j].green;
            pixels_aux[i*2][j*2].blue = pixels[i][j].blue;
        }
    }

    for (int i = 0; i < a_amp; i++){
        for (int j = 0; j < l_amp; j++){
            //Lógica para .red
            if(pixels_aux[i][j].red==0 && i%2==0){
                pixels_aux[i][j].red = (pixels_aux[i][j-1].red + pixels_aux[i][j+1].red)/2;
            } else if(pixels_aux[i][j].red==0 && j%2==0){
                pixels_aux[i][j].red = (pixels_aux[i-1][j].red + pixels_aux[i+1][j].red)/2;
            } else if(pixels_aux[i][j].red==0){
                pixels_aux[i][j].red = (pixels_aux[i-1][j-1].red + pixels_aux[i-1][j+1].red + pixels_aux[i+1][j+1].red + pixels_aux[i+1][j-1].red)/4;
            }

            //Lógica para .green
            if(pixels_aux[i][j].green==0 && i%2==0){
                pixels_aux[i][j].green = (pixels_aux[i][j-1].green + pixels_aux[i][j+1].green)/2;
            } else if(pixels_aux[i][j].green==0 && j%2==0){
                pixels_aux[i][j].green = (pixels_aux[i-1][j].green + pixels_aux[i+1][j].green)/2;
            } else if(pixels_aux[i][j].green==0){
                pixels_aux[i][j].green = (pixels_aux[i-1][j-1].green + pixels_aux[i-1][j+1].green + pixels_aux[i+1][j+1].green + pixels_aux[i+1][j-1].green)/4;
            }

            //Lógica para .blue
            if(pixels_aux[i][j].blue==0 && i%2==0){
                pixels_aux[i][j].blue = (pixels_aux[i][j-1].blue + pixels_aux[i][j+1].blue)/2;
            } else if(pixels_aux[i][j].blue==0 && j%2==0){
                pixels_aux[i][j].blue = (pixels_aux[i-1][j].blue + pixels_aux[i+1][j].blue)/2;
            } else if(pixels_aux[i][j].blue==0){
                pixels_aux[i][j].blue = (pixels_aux[i-1][j-1].blue + pixels_aux[i-1][j+1].blue + pixels_aux[i+1][j+1].blue + pixels_aux[i+1][j-1].blue)/4;
            }
        }
    }

    imprime_arquivo(header.altura, header.largura, pixels_aux, header);

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

    ampliar(header.altura, header.largura, pixels, header);

    return 0;
}