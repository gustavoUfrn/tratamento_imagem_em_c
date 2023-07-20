
# tratamento_imagem_em_c

## Sobre o projeto
**Este projeto foi criado com intuito de avaliar o aprendizado dos alunos da turma de IMD1012 - Introdução às técnicas de programação - T02 (2023.1).**

*Alunos:
Gustavo Alessandro de Oliveira-Araujo - 20220075070
Ewerton Luan Carvalho Silva - 20220043183*

O template do projeto e critérios avaliativo pode ser encontrado no link a seguir: https://github.com/dimap-ufrn/itp-p1#representações-de-imagens-através-de-bitmaps. Neste link também é possível ler mais sobre os detalhes do projeto, como processamento de imagens e suas representações e sobre os formatos de imagem ppm e como modificá-lo.
# Funcionamento do programa
### Entrada de dados, saída de dados e argumentos
O projeto usa entrada e saída padrão de dados, e precisa de um argumento que será usado para selecionar a operação a ser feita. Um exemplos de como podemos usar:

``./nomeProjeto rotate < imgs/galinhos.ppm > imgs/rotate.ppm``

Assim ao rodar o projeto, ele usará o argumento **rotate**, a entrada de dados será o arquivo **imgs/galinhos.ppm** e a saída será o arquivo **imgs/rotate.ppm**.

Ao gerar arquivo gcc é preciso compilar todos os arquivos do código, para isso basta seguir o exemplo abaixo:

``gcc funcoes.h funcoes.h main.c structs.h ``
## Estrutura do código

> Todo o código está comentado, então é possível entender o funcionamento das funções a partir dos comentários. Recomenda-se começar pelo arquivo structs.h.

### structs.h

A definição de tipos que é usada no projeto foi definida no arquivo structs.h. O struct define um cabeçalho que irá conter as informações como, tipo do arquivo, largura, altura, quantidade de pixels e uma matriz de Pixel que é outro struct para armazenar os valores de red, green e blue.
### Main
Antes da main usamos ``#include "funcoes.h"`` que irá chamar o arquivo onde as funcionalidades/funções do projeto estão declaradas.

O Main será responsável por chamar as funções de leitura de arquivo, impressão de arquivo e a função responsável pela escolha da operação.

O argumento que é passado pela main define qual alteração será feita na imagem, as operações estão listadas a seguir:
- *gray*: Cria uma nova imagem em escala de cinza;
- *enlarge*: Ampliar a imagem em 2x;
- *reduce*: Reduz a imagem em 2x;
- *blur*: Cria uma nova imagem com a nitidez reduzida;
-  *sharpening*: Não foi implementada
- *rotate*: Rotaciona a imagem 90° em sentido anti-horário;

### Funcoes.c
Para realizar as definições de cada função usamos funcoes.c que contém todas as funções e importa ``#include "funcoes.h"``.
> As definições de cada uma das funções serão explicadas no próximo tópico.

### Funcoes.h
O arquivo funcoes.h normalmente é responsável por conter as declarações de tipos das funções. Além de fazer a chamada dos recursos básicos do código, como importação de bibliotecas e por isso também importará ``#include "structs.h"``
## Definições de funções do projeto (funcoes.h)

> A maioria das funções usam como parâmetros o ponteiro para header, para que possam ser feitas alterações em header em outros escopo do projeto.

### matriz_pixels

A função matriz_pixels irá fazer alocação dinâmica necessária para salvar uma matriz de Pixels em header com base na altura e largura passadas pelo header.

### ler_arquivo

A função ler_arquivo será responsável pela a leitura do arquivo usando a entrada padrão de dados, esta função chama matriz_pixels para que depois as informações lidas sejam salvas no espaço que foi alocado.

### ler_argumentos

A função ler_argumentos é responsável por pegar o argumento da função main e retorná-lo apenas com o nome da primeira operação que será usada, e que será repassada para função de operações pela Main.

Esta função usa de parâmetros a quantidade de argumentos que foi repassada e a matriz de argumentos. Além de avisar ao usuário se não foram passados nenhum argumento.

### operacao

A função de operação irá usar o ponteiro char que foi retornado por ler_argumentos e a biblioteca de string para comparar com a operação que será feita. Após a comparação, a função irá chamar outra função como, gray, blur, rotate...

Como parâmetro dessa função, além do ponteiro char que será usada para a comparação é preciso passar header, para que a função seja capaz de chamar outras funções passando o ponteiro de header como parâmetro.

### gray

A função gray percorre a matriz_pixels pegando seus valores de red/green/blue, e fazendo uma média, logo após ela salva o valor da média como novos valores de red/green/blue. Exemplo: Caso o red/green/blue sejam 255, 255, 0, seus novos valores serão 170, 170, 170.

### rotate

A função de rotacionar transforma a imagem por meio de um header auxiliar ``header Header_aux``, este vai ter a altura e largura invertidos, ou seja, no caso de uma matriz 2x3 Header_aux será então 3x2, é necessário que seja alocado um espaço para salvar os novos pixels dessa matriz.

Ao usar o ``for`` precisamos usar a altura e largura normais de Header, e ao percorrer o ``for`` note que fazemos as duas operações a seguir:

- Inverter o [i][j] para [j][i], isso irá espelhar nossa imagem;

- Usando ``[Header->altura - 1 - i]``: Isso fará com que **i** não vai de 0 a altura, e sim de altura a 0, permitindo com que nossa matriz fique de ponta a cabeça.

A combinação dessas duas operações na matriz faz com que nossa matriz gira 90° em sentido anti-horário, que serão salvos em Header_aux.

Para terminar alteramos a altura e largura de Header pelos de Header_aux, liberamos o espaço alocado da matriz de Header e usamos e informamos que seu novo valor será a da matriz em ``Header_aux.pixel_img``.

### blur

A função blur foi feita usando o site abaixo como consulta, ele fala sobre a implementação do desfoque gaussiano e como funciona.
https://medium.com/turing-talks/implementa%C3%A7%C3%A3o-do-desfoque-gaussiano-d6e21e314920

A função blur precisa de três variáveis extra de média, uma para cada pixel correspondente, assim teremos media_red, media_green e media_blue. Para que a alteração blur seja feita corretamente precisamos pegar os pixels em uma área 3x3 e criar uma média desse valor e por final aplicar a média respectivamente nos pixels que foram pegos na matriz 3x3, os pixels da borda não podem ser usados nesse caso por que a matriz 3x3 ficaria fora do escopo da matriz.

Para que a borda do código seja evitada gerando erros no código, precisamos de um ``if`` que evite usar o ``I e J`` nos valores 0 e nos valores de ``altura e largura``.

Para finalizar, atualizamos os valores de ``Header_aux.pixel_img`` usando um ``for`` para percorrer a matriz 3x3, porém com uma linha e coluna a menos, ao invés de usar o pixel do meio.
### sharpening
A função sharpening ainda não foi implementada.
### enlarge
A função enlarge primeiramente amplia a altura e largura da matriz da estrutura de dados que é passado como parâmetro. Para realizar o cálculo necessário basta multiplicar a matriz por 2 e diminuir em 1: ``Header->altura + (Header->altura-1)``. Em seguida precisamos zerar o Header_aux que será criado com base nos novos valores de altura e largura.

Ao criar uma variavel Header_aux que precisaremos para alocar a nova matriz aumentada, usamos os valores da matriz anterior para gerar uma matriz onde os valores da velha serçao separados em linhas e colunas por zeros.

Para que isso aconteça basta percorrer a matriz com os valores iniciais de altura e largura, multiplicá-los por dois e salva-los na nova matriz: ``Header_aux.pixel_img[i*2][j*2] = Header->pixel_img[i][j]``

A partir dai o próximo ``for`` percorre a matriz com altura_ampliada e largura_ampliada, usando três if para preencher os zeros que ainda restam nas matrizes.

- O primeiro ``if`` faz o cálculo da linha i, modificando o 0 para uma média dos seus valorres adjacentes;
- O segundo ``if`` faz o cálculo da linha j, modificando o 0 para uma média entre os valores que estão acima e abaixo.
- O terceiro``if`` faz o cálculo dos zeros que sobraram, modificando-o para uma média entre os valores adjacentes, acima e abaixo.

E novamente podemos repassar os dados que estão em Header_aux para Header, incluindo altura, largura e a parte alocada em Header_aux.pixel_img.
### reduce
A função reduce tem como base também a função enlarge, porém algumas lógicas são diferentes.
Para entender como reduce funciona, pense como exemplo a matriz 4x4 ira gerar uma matriz 2x2, e que os valores são usados como médias para formar a nova base.

O código ``Header_aux.pixel_img[i][j] = (Header->pixel_img[i*2][j*2] + Header->pixel_img[i*2+1][j*2] + Header->pixel_img[i*2][j*2+1] + Header->pixel_img[i*2+1][j*2+1])/4;`` é responsável pela lógica de redução da matriz.

Ao usar ``Header->pixel_img[i*2][j*2]`` eu permito que minha matriz pequena alcance o tamanho da matriz maior, e os outros valores são somados com o inicial para fazre uma média, de forma resumida irá pegar os valores que estão a sua volta para servir de média.

### imprime_arquivo
A função imprime arquivo usa a saída padrão de dados para criar um novo arquivos com os dados de Header que são passados como parâmetro, e após a impressão ele libera o espaço que foi alocado para ``Header->pixel_img``.
