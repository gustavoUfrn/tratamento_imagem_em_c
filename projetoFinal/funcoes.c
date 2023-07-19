#include "funcoes.h"

void MatrizPixels(ptn_header Header){
    int i;

	Header->pixel_img = (Pixel**)malloc(Header->altura * sizeof(Pixel*));
	for(i = 0; i < Header->altura; i++){
		Header->pixel_img[i] = (Pixel*)malloc(Header->largura * sizeof(Pixel));
	}
}

void ler_arquivo(ptn_header Header){
    int i, j;
    
    scanf("%s\n", Header->p);
    scanf("%d %d\n", &Header->largura, &Header->altura);
    scanf("%d\n", &Header->tam_rgb);

    MatrizPixels(Header);    

    // Leitura da matriz que está no arquivo de acordo com altura e largura.
    for(i=0; i<Header->altura; i++){
        for(j=0; j<Header->largura; j++){
            scanf("%d %d %d", &Header->pixel_img[i][j].red, &Header->pixel_img[i][j].green, &Header->pixel_img[i][j].blue);
        }
    }

    return;
}

char* lerArgumentos(int pnt_int, char **pnt_char){
    int i=1;

    if(pnt_int == 2){      
        return pnt_char[1];
    } else {
        printf("Seu argumento esta digitado incorretamente! Passe um dos argumentos: ");
    }
};
// Comando principal de entrada de dados. É com essa função que determina qual efeito será aplicado na imagem.

void operacao(char* Operacao, ptn_header Header){

    if( strcmp(Operacao, "gray_scale") == 0){
        grayScale(Header);
    } else if( strcmp(Operacao, "blur") == 0){
        blur(Header);
    } else if( strcmp(Operacao, "ampliar") == 0){
        ampliar(Header);
    } else if( strcmp(Operacao, "reduzir") == 0){
        reduzir(Header);
    } else if( strcmp(Operacao, "rotate") == 0){
        rotate(Header);
    }
};
// //  Código para transfomrar a imagem em uma de escala cinza: dentro do loop aninhado, a função itera sobre cada pixel da imagem. Para cada pixel, é calculada a média dos valores de vermelho, 
verde e azul. Essa média é armazenada em uma variável chamada media. Em seguida, os valores de vermelho, verde e azul do pixel são atualizados para 
o valor da média calculada, o que resulta em uma imagem em escala de cinza.

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

void rotate(ptn_header Header){
    int i, j;

    header Header_aux;
    
    Header_aux.altura = Header->largura;
    Header_aux.largura = Header->altura;

    MatrizPixels(&Header_aux);

    for (i = 0; i <  Header->altura; i++) {
        for (j = 0; j < Header->largura; j++) {
            Header_aux.pixel_img[j][Header->altura - 1 - i].red = Header->pixel_img[i][j].red;
            Header_aux.pixel_img[j][Header->altura - 1 - i].green = Header->pixel_img[i][j].green;
            Header_aux.pixel_img[j][Header->altura - 1 - i].blue = Header->pixel_img[i][j].blue;
        }
    }

    Header->altura = Header_aux.altura;
    Header->largura = Header_aux.largura;

    free(Header->pixel_img);
    Header->pixel_img = Header_aux.pixel_img;
}

void blur(ptn_header Header){
    int media_red, media_green, media_blue;
    header Header_aux;    

    Header_aux.altura = Header->altura;
    Header_aux.largura = Header->largura;

    MatrizPixels(&Header_aux);

    for(int i=0; i<Header->altura; i++){
        for(int j=0; j<Header->largura; j++){
            if((i!=0 && j!=0) && (i!=(Header->altura)-1 && j!=(Header->largura)-1)){
                //Lógica para red
                media_red = (Header->pixel_img[i-1][j-1].red + Header->pixel_img[i-1][j].red + Header->pixel_img[i-1][j+1].red +
                              Header->pixel_img[i][j-1].red + Header->pixel_img[i][j].red + Header->pixel_img[i][j+1].red + 
                               Header->pixel_img[i+1][j-1].red + Header->pixel_img[i+1][j].red + Header->pixel_img[i+1][j+1].red)/9;
                //Lógica para green
                media_green = (Header->pixel_img[i-1][j-1].green + Header->pixel_img[i-1][j].green + Header->pixel_img[i-1][j+1].green +
                                Header->pixel_img[i][j-1].green + Header->pixel_img[i][j].green + Header->pixel_img[i][j+1].green + 
                                 Header->pixel_img[i+1][j-1].green + Header->pixel_img[i+1][j].green + Header->pixel_img[i+1][j+1].green)/9;
                //Lógica para blue
                media_blue = (Header->pixel_img[i-1][j-1].blue + Header->pixel_img[i-1][j].blue + Header->pixel_img[i-1][j+1].blue +
                                Header->pixel_img[i][j-1].blue + Header->pixel_img[i][j].blue + Header->pixel_img[i][j+1].blue + 
                                 Header->pixel_img[i+1][j-1].blue + Header->pixel_img[i+1][j].blue + Header->pixel_img[i+1][j+1].blue)/9;
                          
                for(int o=i-1; o<Header->altura; o++){
                    for(int p=j-1; p<Header->largura; p++){
                        Header_aux.pixel_img[o][p].red = media_red;
                        Header_aux.pixel_img[o][p].green = media_green;
                        Header_aux.pixel_img[o][p].blue = media_blue;
                    }
                }
            }
            media_red=0;
            media_green=0;
            media_blue=0;
        }
    }

    free(Header->pixel_img);
    Header->pixel_img = Header_aux.pixel_img;
}

void ampliar(ptn_header Header){
    int altura_ampliada = Header->altura + (Header->altura-1);
    int largura_ampliada = Header->largura + (Header->largura-1);

    header Header_aux;

    Header_aux.altura = altura_ampliada;
    Header_aux.largura = largura_ampliada;
    MatrizPixels(&Header_aux);

    for (int i = 0; i < altura_ampliada; i++){
        for (int j = 0; j < largura_ampliada; j++){
            Header_aux.pixel_img[i][j].red = 0;
            Header_aux.pixel_img[i][j].green = 0;
            Header_aux.pixel_img[i][j].blue = 0;
        }
    }

    for (int i = 0; i < Header->altura; i++){
        for (int j = 0; j < Header->largura; j++){
            Header_aux.pixel_img[i*2][j*2].red = Header->pixel_img[i][j].red;
            Header_aux.pixel_img[i*2][j*2].green = Header->pixel_img[i][j].green;
            Header_aux.pixel_img[i*2][j*2].blue = Header->pixel_img[i][j].blue;
        }
    }

    for (int i = 0; i < altura_ampliada; i++){
        for (int j = 0; j < largura_ampliada; j++){
            //Lógica para .red
            if(Header_aux.pixel_img[i][j].red==0 && i%2==0){
                Header_aux.pixel_img[i][j].red = (Header_aux.pixel_img[i][j-1].red + Header_aux.pixel_img[i][j+1].red)/2;
            } else if(Header_aux.pixel_img[i][j].red==0 && j%2==0){
                Header_aux.pixel_img[i][j].red = (Header_aux.pixel_img[i-1][j].red + Header_aux.pixel_img[i+1][j].red)/2;
            } else if(Header_aux.pixel_img[i][j].red==0){
                Header_aux.pixel_img[i][j].red = (Header_aux.pixel_img[i-1][j-1].red + Header_aux.pixel_img[i-1][j+1].red + Header_aux.pixel_img[i+1][j+1].red + Header_aux.pixel_img[i+1][j-1].red)/4;
            }

            //Lógica para .green
            if(Header_aux.pixel_img[i][j].green==0 && i%2==0){
                Header_aux.pixel_img[i][j].green = (Header_aux.pixel_img[i][j-1].green + Header_aux.pixel_img[i][j+1].green)/2;
            } else if(Header_aux.pixel_img[i][j].green==0 && j%2==0){
                Header_aux.pixel_img[i][j].green = (Header_aux.pixel_img[i-1][j].green + Header_aux.pixel_img[i+1][j].green)/2;
            } else if(Header_aux.pixel_img[i][j].green==0){
                Header_aux.pixel_img[i][j].green = (Header_aux.pixel_img[i-1][j-1].green + Header_aux.pixel_img[i-1][j+1].green + Header_aux.pixel_img[i+1][j+1].green + Header_aux.pixel_img[i+1][j-1].green)/4;
            }

            //Lógica para .blue
            if(Header_aux.pixel_img[i][j].blue==0 && i%2==0){
                Header_aux.pixel_img[i][j].blue = (Header_aux.pixel_img[i][j-1].blue + Header_aux.pixel_img[i][j+1].blue)/2;
            } else if(Header_aux.pixel_img[i][j].blue==0 && j%2==0){
                Header_aux.pixel_img[i][j].blue = (Header_aux.pixel_img[i-1][j].blue + Header_aux.pixel_img[i+1][j].blue)/2;
            } else if(Header_aux.pixel_img[i][j].blue==0){
                Header_aux.pixel_img[i][j].blue = (Header_aux.pixel_img[i-1][j-1].blue + Header_aux.pixel_img[i-1][j+1].blue + Header_aux.pixel_img[i+1][j+1].blue + Header_aux.pixel_img[i+1][j-1].blue)/4;
            }
        }
    }

    Header->altura = altura_ampliada;
    Header->largura = largura_ampliada;

    free(Header->pixel_img);
    Header->pixel_img = Header_aux.pixel_img;
}

void reduzir(ptn_header Header){

    header Header_aux;

    Header_aux.altura = Header->altura/2;
    Header_aux.largura = Header->largura/2;
    MatrizPixels(&Header_aux);

    Header->altura = Header_aux.altura;
    Header->largura = Header_aux.largura;

    for(int i=0; i< Header->altura; i++){
        for(int j=0; j< Header->largura; j++){
            Header_aux.pixel_img[i][j].red = (Header->pixel_img[i*2][j*2].red + Header->pixel_img[i*2+1][j*2].red + Header->pixel_img[i*2][j*2+1].red + Header->pixel_img[i*2+1][j*2+1].red)/4;
            Header_aux.pixel_img[i][j].green = (Header->pixel_img[i*2][j*2].green + Header->pixel_img[i*2+1][j*2].green + Header->pixel_img[i*2][j*2+1].green + Header->pixel_img[i*2+1][j*2+1].green)/4;
            Header_aux.pixel_img[i][j].blue = (Header->pixel_img[i*2][j*2].blue + Header->pixel_img[i*2+1][j*2].blue + Header->pixel_img[i*2][j*2+1].blue + Header->pixel_img[i*2+1][j*2+1].blue)/4;
        }
    }
    
    free(Header->pixel_img);
    Header->pixel_img = Header_aux.pixel_img;
}

void imprime_arquivo(ptn_header Header){
    int i, j;

    printf("%s\n", Header->p);
    printf("%d %d\n", Header->largura, Header->altura);
    printf("%d\n", Header->tam_rgb);

    for(i=0; i<Header->altura; i++){
        for(j=0; j<Header->largura; j++){
            printf("%3d %3d %3d ", Header->pixel_img[i][j].red, 
                                                Header->pixel_img[i][j].green, 
                                                    Header->pixel_img[i][j].blue);
        }
        printf("\n");
    }

    free(Header->pixel_img);
}

