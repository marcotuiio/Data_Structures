#include <stdio.h>

int main(){
    int x1, x2, x3, x4;
    int *menor;

    printf("Infome x1: ");
    scanf("%d", &x1);
    printf("Infome x2: ");
    scanf("%d", &x2);
    printf("Infome x3: ");
    scanf("%d", &x3);
    printf("Infome x4: ");
    scanf("%d", &x4);

    if(x1 < x2){
        menor = &x1;
    }else{
        menor = &x2;
    }
    if(x3 < *menor){
        menor = &x3;
    }
    if(x4 < *menor){
        menor = &x4;
    }
    printf("O menor numero foi %d\n", *menor);

    return 0;
}