# Estrutura-de-Dados
Colocar arquivos de Ed para facilitar estudos

1- em fila_circ, descobrir e corrigir o problema do Item void pointer ===>> RESOLVIDOOO

2- Descobrir um meio de percorrer com eficiência os elementos das lista ---> FEITO <3 Rodrigo god 
    * criar novo void pointer que retorna a celula (typedef void* Cell) 
    e utilizarm no getFirst ===> RESOLVIDOOO
    * extrair e montar as figuras em svg.c ===> RESOLVIDOOO
    ---> FEITO  Rodrigo god sagrado divino

3- Nos arquivos de circulo, retangulo, linha e texto os valores extraidos do geo funcionam corretamente, fora dali fica tudo estranho  ====> RESOLVIDO
    * ver em geo.c
    * ver em svg.c (nas funções get)

4- Concatenação de geo e qry para gerar nome do svg ===> RESOLVIDO

5- Descobrir e arrumar erros na criação do txt pós qry ==> RESOLVIDO

6- Quando roda com o qry exibir tambem o svg puro, junto com o svg pos qry e o txt  ==> RESOLVIDO

==================================================================================================

 * Próximo passo: continuar a implementar o .qry ;-;
    -> arrumar os comando UPS, POL, SEL+
      * em pol "SO" falta fazer as linhas de preenchimento
      * em ups talvez esteja bem merda  ==> Parece que funciona mas não confio muito nele
      * em sel+ ta igual a sel ??? Devo considerar as areas selecionadas anteriormente e comparar com um grandee retângulo  ==> Parece que funciona mas não confio muito nele
    -> arrumar seg fault em DELS (URGENTE!!!) e talvez remover as figuras selecionadas do svg ==> resolvido? 

./ted -e /home/marcotuiio/EDor/T1/input -f escada-20.geo -o /home/marcotuiio/EDor/T1/output -q 002esc.qry

./ted -e /home/marcotuiio/EDor/T1/input -f casa-campo.geo -o /home/marcotuiio/EDor/T1/output -q 006ups.qry

./ted -e /home/marcotuiio/EDor/T1/input -f esp-2v-tt.geo -o /home/marcotuiio/EDor/T1/output -q 002esp2v.qry

./ted -e /home/marcotuiio/EDor/T1/input -f esp-ln-az.geo -o /home/marcotuiio/EDor/T1/output -q 002esp.qry

./ted -e /home/marcotuiio/EDor/T1/input -f hinosp1.geo -o /home/marcotuiio/EDor/T1/output -q 008h.qry

./ted -e /home/marcotuiio/EDor/T1/input -f hinosp2.geo -o /home/marcotuiio/EDor/T1/output -q 007h2.qry

./ted -e /home/marcotuiio/EDor/T1/input -f vaso-flor.geo -o /home/marcotuiio/EDor/T1/output -q 006v.qry

./ted -e /home/marcotuiio/EDor/T1/input -f jog-sp.geo -o /home/marcotuiio/EDor/T1/output -q 007j.qry

./ted -e /home/marcotuiio/EDor/T1/input -f hinotxt.geo -o /home/marcotuiio/EDor/T1/output 

!!!PEDIR AJUDAR SEGUNDA PRO PROFESSOR EM POL(LINHAS INTERNAS), SEL+(TA CERTO?), UPS(TA CERTO?)!!!