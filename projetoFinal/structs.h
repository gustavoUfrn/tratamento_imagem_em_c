
typedef struct {
    int red, green, blue;
} Pixel;

typedef struct {
    Pixel **pixel_img;
    char p[3];
    int altura, largura, tam_rgb;
} header,  *ptn_header;