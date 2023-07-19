#include "funcoes.h"

int main(int argc, char *argv[]){
    
    header Header;

    ler_arquivo(&Header);

    char* result = lerArgumentos(argc, argv);
    operacao(result, &Header);

    imprime_arquivo(&Header);

    return 0;
}