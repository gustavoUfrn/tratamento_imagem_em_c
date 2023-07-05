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

    out_file = fopen("galinhos_rot.ppm", "wt");
    
    if(out_file == NULL){
        printf("Erro ao abrir o arquivo!");
    } else {
        fprintf(out_file, "%s\n", header.tipo_p);
        fprintf(out_file, "%d %d\n", header.altura, header.largura);
        fprintf(out_file, "%d\n", header.tam_rgb);
    }

    a = header.largura;
    l = header.altura;

    for(i=0; i<a; i++){
        for(j=l-1; j>=0; j--){
            fprintf(out_file, "%3d %3d %3d ", pixels[j][i].red, pixels[j][i].green, pixels[j][i].blue);
        }
        fprintf(out_file, "\n");
    }

    fclose(out_file);

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
    imprime_arquivo(header.altura, header.largura, pixels, header);

    return 0;
}