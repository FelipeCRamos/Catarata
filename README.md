## Projeto de ITP - 2017.2
### Software para Diagnóstico de Catarata

Alunos envolvidos no projeto:
- Felipe Ramos
- João Pedro Amorim

### Informações sobre o projeto
Neste projeto, iremos implementar um programa em C para analisar 4 imagens (duas com catarata e duas sem catarata) e emitir um diagnóstico de cada uma.
O projeto irá ser implementado nas seguintes etapas:
- 1. **Transformação da imagem colorida para tons de cinza**  
Para converter qualquer cor em seu nível aproximado de cinza, deve-se primeiro obter suas primitivas vermelho, verde e azul (da escala Red Green Blue). Adiciona-se então 30% do vermelho mais 59% do verde mais 11% do azul, independente da escala utilizada (0.0 a 1.0, 0 a 255, 0% a 100%.) O nível resultante é o valor de cinza desejado. Tais porcentagens estão relacionadas a própria sensibilidade visual do olho​ humano​ convencional​ para​ as​ cores​ primárias.  
- 2. **Segmentação da imagem**  
A filtragem é um procedimento usual ao realizar o tratamento de uma imagem, antes de que um determinado processamento possa ser feito. De uma forma geral a filtragem de imagens é implementada através de uma multiplicação especial entre duas​ matrizes​ (operação​ também​ chamada​ de​ convolução).
![somatório](https://latex.codecogs.com/gif.latex?Ires(x,&space;y)&space;=&space;\sum_{a=-M/2}^{M/2}&space;\sum_{b=-N/2}^{N/2}&space;f(a&plus;&space;M/2,&space;b&space;&plus;&space;N/2)&space;Iorig(X&plus;a,&space;y&space;&plus;&space;b))  
Na *Equação 1*, *Ires* e *Iorig* representam, respectivamente, a imagem resultante após a filtragem e a imagem original a ser filtrada; *Ires*(x,y) e *Iorig*(x,y) representam os pixels das imagens nas posições **x** e **y** de cada uma. Os valores de **M** e **N** são os tamanhos da matriz **F**, que é o filtro a ser aplicado. Existem diversas utilizações para filtragem tais como remoção ou adição de ruído na imagem e mudança ou realce de algumas características. Neste trabalho iremos aplicar dois filtros na imagem: o **Filtro Gaussiano​** e ​o **Filtro​ de​ Realce​ de​ Arestas**.  
O **filtro gaussiano** é um dos mais comuns em processamento digital de imagens, pois ele reduz as transições bruscas na imagem (ruídos de alta frequência), deixando a imagem mais “suave”. Na prática o filtro gaussiano é implementado através da operação de filtragem especificada na Equação 1 usando uma matriz F, obtida através de uma função gaussiana 2D. Para o nosso caso, usaremos os valores​ para​ *F* como​ mostrados​ na​ Figura​ 1,​ abaixo:
![matriz](https://latex.codecogs.com/gif.latex?\frac{1}{159}&space;\begin{bmatrix}&space;&2&space;&4&space;&5&space;&4&space;&2&space;\\&space;&4&space;&9&space;&12&space;&9&space;&4&space;\\&space;&5&space;&12&space;&15&space;&12&space;&5&space;\\&space;&4&space;&9&space;&12&space;&9&space;&4&space;\\&space;&2&space;&4&space;&5&space;&4&space;&2&space;\end{bmatrix})  
**Realce de Arestas** é um processo de realce de arestas na imagem. Esse processo recebe como entrada uma imagem e produz como saída outra imagem, porém contendo apenas os contornos da imagem original, em preto e branco. Para muitos procedimentos que precisam da detecção de figuras geométricas, como círculos, no nosso caso, é necessário o uso de imagens que contenham apenas os contornos das figuras na imagem ao invés dos valores de todos os pixels em RGB. Para tal é necessário realizar uma série de procedimentos a fim de garantir a detecção dos contornos com a melhor qualidade possível.
