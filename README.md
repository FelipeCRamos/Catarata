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