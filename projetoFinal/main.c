//Importação do funcoes.h, contendo todas as bibliotecas usadas e arquivos de tipos
#include "funcoes.h"

// Main para gente grande xD (Função main que recebe argumentos)
int main(int argc, char *argv[]){
    
    // Cria um header
    header Header;

    // Chama a função ler_arquivo, capaz de ler o arquivo e alocar suas variaveis dinamicamente
    ler_arquivo(&Header);

    // Chamada da funcao que salva o na variavel ponteiro result o texto da operação que foi digitada como argumento
    char* result = ler_argumentos(argc, argv);
    // Chamada da funcao que ira comparar o valor passado com os valores de operações possiveis
    operacao(result, &Header);

    // Chama a função de imprimir o arquivo, também libera o espaço que foi alocado
    imprime_arquivo(&Header);

    return 0;
}