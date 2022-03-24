#include <stdio.h>
#include <math.h>

int main (){
    float n1, div, s, aux;
    aux = 0;
    div = 50;

for(n1=1; n1<=50; n1+=1){
    s = ( pow(2, n1) / div ) + aux;
    aux = s;
    div = div - 1;
}

printf("O valor de S foi %.1f", s);

    return 0;
}