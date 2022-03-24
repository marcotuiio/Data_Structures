#include <stdio.h>

int main(){
    int y, *p, x;
    
    y = 0;
    p = &y;     //p apontado para endereço de y
    x = *p;     //x recebe o conteúdo apontado por p, x=0
    x = 4;      //x recebe 4
    (*p)++;     //conteúdo apontado por p recebe +1
    x--;        //x perde 1
    (*p) += x;  //conteúdo apontado por p recebe +3, ou seja, y que é 1 soma 3, y=4

        printf ("y = %d\n", y);

 return(0);
} 

//p = &vetor[2]   p está apontado para a memória com o elemento de indicie 2
//p2 = p+1        p2 está apotado pata a memória seguinte com relação a p
//*p2 = *p+1      conteúdo apontado por p2 recebe conteúdo apontado por p +1
//*p = 5          conteúdo apontado por p2 é 5 
//*(p+4) = 2      4 posições depois da posição de p é igual 2
//*(p+4) +1       4 posições depois da posição de p soma-se 1, ou seja, *(p+4) +1 = 2+1 = 3

