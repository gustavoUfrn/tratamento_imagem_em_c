#include "funcoes.h"

int main(){
    
    header Header;

    lerImagem(&Header);

    // grayScale(&Header);

    blur(&Header);

    imprime_arquivo(&Header);

    return 0;
}