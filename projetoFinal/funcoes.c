#include "funcoes.h"

void MatrizPixels(ptn_header Header){
    int i;

	Header->pixel_img = (Pixel**)malloc(Header->altura * sizeof(Pixel*));
	for(i = 0; i < Header->altura; i++){
		Header->pixel_img[i] = (Pixel*)malloc(Header->largura * sizeof(Pixel));
	}
}

void lerImagem(ptn_header Header){
    int i, j;
    FILE *arquivo;

    arquivo = fopen("galinhos.ppm", "rt");

    if(arquivo == NULL){
        printf("Erro ao ler arquivo!\n");
    }

    fscanf(arquivo, "%s\n", Header->p);
    fscanf(arquivo, "%d %d\n", &Header->largura, &Header->altura);
    fscanf(arquivo, "%d\n", &Header->tam_rgb);

    MatrizPixels(Header);    

    // Leitura da matriz que está no arquivo de acordo com altura e largura.
    for(i=0; i<Header->altura; i++){
        for(j=0; j<Header->largura; j++){
            fscanf(arquivo, "%d %d %d", &Header->pixel_img[i][j].red, &Header->pixel_img[i][j].green, &Header->pixel_img[i][j].blue);
        }
    }

    fclose(arquivo);
}

void grayScale(ptn_header Header) {
    int i, j;

    for(i=0; i<Header->altura; i++){
        for(j=0; j<Header->largura; j++){
            int gray_value = 0;
            gray_value = (Header->pixel_img[i][j].red + Header->pixel_img[i][j].green + Header->pixel_img[i][j].blue)/3;
            Header->pixel_img[i][j].red = gray_value;
            Header->pixel_img[i][j].green = gray_value;
            Header->pixel_img[i][j].blue = gray_value;
        }
    }

    return;
}

void imprime_arquivo(ptn_header Header){
    int i, j;

    FILE *out_file;

    out_file = fopen("galilhos_blur.ppm", "wt");

    if(out_file == NULL){
        printf("Erro ao abrir o arquivo!");
        return;
    }

    fprintf(out_file, "%s\n", Header->p);
    fprintf(out_file, "%d %d\n", Header->largura, Header->altura);
    fprintf(out_file, "%d\n", Header->tam_rgb);

    for(i=0; i<Header->altura; i++){
        for(j=0; j<Header->largura; j++){
            fprintf(out_file, "%3d %3d %3d ", Header->pixel_img[i][j].red, 
                                                Header->pixel_img[i][j].green, 
                                                    Header->pixel_img[i][j].blue);
        }
        fprintf(out_file, "\n");
    }

    fclose(out_file);

    free(Header->pixel_img);
}

