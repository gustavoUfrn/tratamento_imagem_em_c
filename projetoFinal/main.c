//Importa a biblioteca de funcoes que foi criada (funcoes.h)
#include "funcoes.h"

//Main pegando argumentos, o arquivo esta sendo nomeado "a.exe"
int main(int argc, char *argv[]){
    
    header Header;
    lerImagem(&Header);

    char* result = lerArgumentos(argc, argv);
    operacao(result, &Header);

    imprime_arquivo(result, &Header);

    return 0;
}