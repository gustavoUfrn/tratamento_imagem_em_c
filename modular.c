#include <stdio.h>

int main(int argc, char const *argv[]){
    
    int i;

    if(argc>1){
        printf("Foram inserirdos %d argumentos!\n", argc);
        for(i=0; i<argc; i++){
            printf("%s\n", argv[i]);
        }
    } else {
        printf("Não foram digitados argumentos!");
    }

    return 0;
}
