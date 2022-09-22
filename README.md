# DATA STRUCTURES

** TO DO t3
- Teste se miminum bounding box de subarvore e no funcionam
- Testar casos do qry
Arvore está se deformando
Se a remoção não funciona, nada funciona. 
- ARRUMAR REMOÇÃO 
- e: ok
- mv: +-  Remover e reinserir com x e y atualizados, remoção não é confiável
- lr: ok  So remover
- d: ok  So Remover
- mc: +-  Remover e reinserir com x e y atualizados, remoção não é confiável

OBS COM TESTES, QUEBRAM ARVORE:

./ted -e /home/marcotuiio/inputs -o /home/marcotuiio/outputs -f 04-mar-grande.geo -q 04-mar-grande/mixed.qry

./ted -e /home/marcotuiio/inputs -o /home/marcotuiio/outputs -f 04-mar-grande.geo -q 04-mar-grande/mc-02-3x4.qry

./ted -e /home/marcotuiio/inputs -o /home/marcotuiio/outputs -f 03-mar-medio.geo -q 03-mar-medio/mixed.qry

./ted -e /home/marcotuiio/inputs -o /home/marcotuiio/outputs -f 03-mar-medio.geo -q 03-mar-medio/mc-02-3x4.qry

./ted -e /home/marcotuiio/inputs -o /home/marcotuiio/outputs -f 02-mar-pequeno-3pares-naus.geo -q 02-mar-pequeno-3pares-naus/mc-02-3x4.qry

./ted -e /home/marcotuiio/inputs -o /home/marcotuiio/outputs -f 01-mar-pequeno-1par-naus.geo -q 01-mar-pequeno-1par-naus/mc-02-3x4.qry