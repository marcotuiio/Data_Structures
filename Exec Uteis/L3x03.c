#include <stdio.h>

int main(){
    int n, a, b, c;

    printf("Digite um valor inteiro positivo: ");
    scanf("%d", &n);

    for(a=1; a<=n; a++){
        for(b=1; b<=a; b++){
            printf("%d", b);
        }
        c = a - 1;
        while(c >= 1){
            printf("%d", c);
            c = c - 1;
        }
        printf("\n");
    }

    return 0;
}