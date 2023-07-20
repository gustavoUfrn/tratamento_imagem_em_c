#include "funcoes.h"

// A maioria das funções usa como parâmetro o ponteiro de Header para que seja possivel fazer alterações na matriz ou nas variaveis de altura e largura.

// Após usar Header_aux podemos liberar o espaço alocado em Header, e tornar os valores de Header_aux como o novo de Header(desalocado na função imprime_arquivo).

// matriz_pixels ira fazer alocação dinamica da matriz pixel_img que esta em header, com base na altura, largura e o tamanho de Pixel.
// Ira receber como parâmetro Header, para que seja póssivel acessar pixel_img, altura e largura.
void matriz_pixels(ptn_header Header){
    int i;

	Header->pixel_img = (Pixel**)malloc(Header->altura * sizeof(Pixel*));
	for(i = 0; i < Header->altura; i++){
		Header->pixel_img[i] = (Pixel*)malloc(Header->largura * sizeof(Pixel));
	}
}

// ler_arquivo vai usar a entrada de dados padrão para salvar os dados em header e no valor alocado pixel_img.
// Para isso é necessario chamar matriz_pixels passando header como parêmetro.
void ler_arquivo(ptn_header Header){
    int i, j;
    
    scanf("%s\n", Header->p);
    scanf("%d %d\n", &Header->largura, &Header->altura);
    scanf("%d\n", &Header->tam_rgb);

    matriz_pixels(Header);    

    // Leitura da matriz que está no arquivo de acordo com altura e largura.
    for(i=0; i<Header->altura; i++){
        for(j=0; j<Header->largura; j++){
            scanf("%d %d %d", &Header->pixel_img[i][j].red, &Header->pixel_img[i][j].green, &Header->pixel_img[i][j].blue);
        }
    }

    return;
}

// ler_arguentos vai precisa como parâmetro o inteiro que é passado como argumento e ponteiro que contém os argumentos.
// Essa função vai retorna o ponteiro char com o argumento que foi repassada para ao executar o arquivo.
char* ler_argumentos(int pnt_int, char **pnt_char){
    int i=1;

    if(pnt_int == 2){      
        return pnt_char[1];
    } else {
        printf("Seu argumento esta digitado incorretamente! Passe um dos argumentos: ");
    }
};

// Usa como parâmetro header que será passado para a função de alteração de imagem que será usada em seguida, e também o ponteiro com
// o parâmetro da função ler_argumentos
// Para que a próxima função seja chamada comparamos a variavel Operacao com a string da função usando strcmp que deverá ser usada em seguida.
void operacao(char* Operacao, ptn_header Header){

    if( strcmp(Operacao, "gray") == 0){
        gray(Header);
    } else if( strcmp(Operacao, "rotate") == 0){
        rotate(Header);
    } else if( strcmp(Operacao, "blur") == 0){
        blur(Header);
    } else if( strcmp(Operacao, "enlarge") == 0){
        enlarge(Header);
    } else if( strcmp(Operacao, "reduce") == 0){
        reduce(Header);
    } else if( strcmp(Operacao, "sharp") == 0){
        //sharpening(Header);
    }
};

// Quando chamada a função vai usar os valores dos pixels red/green/blue em uma posição no array para criar uma média, após isso os pixels red/green/blue
// precisamos redefinir os valores dos pixels red/green/blue usados para essa média
void gray(ptn_header Header) {
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

// Rotate usa a variavel Header_aux vai armazenar os novos valores de altura e largura, além dos novos valores da matriz
// note que é preciso alocar um espaço apra Header_aux
// Para que seja possivel rotacionar basta espelhar a matriz e depois inverte-lá (ponta-cabeça)
// Header_aux.pixel_img[j][i]; -> Espelha a imagem
// [Header->altura - 1 - i] -> Ao enves de contar de 0 até altura, conta de altura até 0 -> Inverte a matriz
void rotate(ptn_header Header){
    int i, j;

    header Header_aux;
    
    Header_aux.altura = Header->largura;
    Header_aux.largura = Header->altura;

    matriz_pixels(&Header_aux);

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

// Para que a função blur funcionar precisamos ter em mente que os pixels que seram utilizados como base não podem ser o pixels da borda da matriz]
// A parte do código responsavel por evitar isso está no if -> (i!=0 && j!=0) && (i!=(Header->altura)-1 && j!=(Header->largura)-1)
// Ao percorer a Matriz, usamos os pixels que estão a volta do pixel(uma matriz 3x3) escolhido para criar uma média que será aplicada
// em uma matriz 3x3 a partir do pixel inicial (neste caso, não é o pixel central da matriz e sim o pixel em uma linha e coluna antes do pixel central).
void blur(ptn_header Header){
    int media_red, media_green, media_blue;
    header Header_aux;    

    Header_aux.altura = Header->altura;
    Header_aux.largura = Header->largura;

    matriz_pixels(&Header_aux);

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

// Na função de enlarge precisamos que Header_aux armazene os novos valores de altura e largura, que é calculado com o dobro -1 -> ((altura + altura) -1)
// Nesta função é necessario que todos os valores de pixel_img estejam zerados a primeira cadeia de fors é resposavel por zerar a matriz
// A segunda cadeia de fors faz com que os valores da matriz inicial seja expandida, basta multiplicar por dois, assim a matriz incial irá andar
// de um em um, a a matriz aumentada de 2 em 2.
// Após o passo anteiror, a matriz alocada em Header_aux ficará espaçada com zeros(Já que anda de 2 em 2).
// O primeiro if fará com que as linhas sejam preenchidas fazendo uma média dos pixels adjacentes.
// O segundo if será responsavel por preencher as colunas, com a média dos valores acima e abaixo.
// O terceiro if ira preencher os zeros criados com os valores dos pixels adjacentes, acima e abaixo.
void enlarge(ptn_header Header){
    int altura_ampliada = Header->altura + (Header->altura-1);
    int largura_ampliada = Header->largura + (Header->largura-1);

    header Header_aux;

    Header_aux.altura = altura_ampliada;
    Header_aux.largura = largura_ampliada;
    matriz_pixels(&Header_aux);

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

// O reduce usa uma parte da lógica do enlarge, porém usamos os pixels da matriz maior, e usamos como média para criar uma matriz menor,
// Neste caso estamos percorrendo a nova matriz de um em um, porém percorremos a matriz maior de 2 em 2
// Os novos valores da matriz são a media do pixel escolhido, o pixel abaixo, o pixel adjacente da direita e o pixel abaixo adjacente.
void reduce(ptn_header Header){

    header Header_aux;

    Header_aux.altura = Header->altura/2;
    Header_aux.largura = Header->largura/2;
    matriz_pixels(&Header_aux);

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

// Imprime o arquivo com entrada básica de dados e libera o espaço que ainda está sendo utilizado na alocação dinâmica
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
