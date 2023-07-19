# tratamento_imagem_em_c
## Sobre o projeto
**Este projeto foi criado com intuito de avaliar o aprendizado dos alunos da turma de IMD1012 - Introdução às técnicas de programação - T02 (2023.1).**

*Alunos: Gustavo Alessandro de Oliveira Araujo - 20220075070 e Ewerton Luan Carvalho Silva - 20220043183*

O template e críterios avaliativo pode ser encontrado no link a seguir: https://github.com/dimap-ufrn/itp-p1#representações-de-imagens-através-de-bitmaps. Neste link também é possivel ler mais sobre os detalhes do projeto, como processamento de imagens e suas representações e sobre os formatos de imagem ppm e como modifica-lo.
# Funcionamento do programa
### Entrada de dados, saída de dados e argumentos
O projeto usa a entrada e saída padrão de dados, e precisa de uma argumento que será usado para selecionar a operação. Um exemplos que como podemos usar: 

``./nomeProjeto rotate < imgs/galinhos.ppm > imgs/rotate.ppm``

Assim ao rodar o projeto, ele usará o argumento **rotate**, a entrada de dados será o arquivo **imgs/galinhos.ppm** e a saída será o arquivo **imgs/rotate.ppm**.

Ao gerar arquivo gcc é preciso compliar todos os arquivos do código, para isso basta seguir o exemplo abaixo: 
``gcc funcoes.h funcoes.h main.c structs.h ``
## Estrutura do código
### structs.h
A definição de tipos que é usada no projeto foi definida no arquivo structs.h. O struct define um cabeçalho que ira conter as informações como, tipo do arquivo, largura, altura, quantidade de pixels e uma matriz de Pixel que é outro struct para armazenar os valor de red, green e blue.
### Main
Antes da main usamos ``#include "funcoes.h"`` que irá chamar o arquivo onde as funcionalidades/funções do projeto estam declaradas.
O main será responsavel por chamar as funções de leitura de arquivo, impressão de arquivo e escolha de operação.
O argumento receberá o nome da transformação que será usada, estas estão listadas a seguir:

- *gray*: Cria uma nova imagem em escala de cinza;
- *enlarge*: Amplia a imagem em 2x;
- *reduce*: Reduz a imagem em 2x;
- *blur*: Cria uma nova imagem com a nitidez reduzida;
- *rotate*:  Rotaciona a imagem 90° em sentido anit-hórario;
### Funcoes.h
O arquivo funcoes.h normalmente é responsavel por conter as declarações de tipos das funções. Além de fazer a chamada dos recursos básicos do código, como importação de bibliotecas e por isso também importará ``#include "structs.h"``
### Funcoes.c
Para realizar as definições de cada função usamos funcoes.c (contém todas as funções) e importa ``#include "funcoes.h"``.
