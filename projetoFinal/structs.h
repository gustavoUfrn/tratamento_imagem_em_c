// Tipagem da variavel Pixel, assim posso ter uma variavel que armazene diferentes valores em sí,
// É como se fosse uma variavel dentro da outra, Pixel podera acesar red/green/blue, alterando seus valores.
typedef struct {
    int red, green, blue;
} Pixel;

// Tipagem do header, usada armazenar o cabeçalho ppm e também a matriz de Pixel que será criada a partir da largura e altura
// Com a matriz de Pixel podemos atribuir os valores red/green/blue para apenas um valor na matriz
// Exp.: Matriz[0][0].red = 255, Matriz[0][0].green = 0, Matriz[0][0].blue = 0; Isso irá gerar um pixel vermelho na posição [0][0]
typedef struct {
    Pixel **pixel_img;
    char p[3];
    int altura, largura, tam_rgb;
} header,  *ptn_header;