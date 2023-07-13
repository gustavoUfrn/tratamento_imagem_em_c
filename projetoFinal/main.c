#include "funcoes.h"

int main(){
    
    header Header;

    lerImagem(&Header);

    grayScale(&Header);

    imprime_arquivo(&Header);

    return 0;
}