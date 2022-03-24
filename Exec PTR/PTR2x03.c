#include <stdio.h>

int main(){
    int matriz[10][10];
    int i, j;
    int *p;

    p = &matriz[0][0];
    for(i=0; i<100; i++){
        *(p + i) = 1;
    } 

    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("%d ", *(p+i*10+j));
        }
        printf("\n");
    }

    return 0;
}