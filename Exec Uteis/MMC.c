#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c, mmc, div;
    int a1, b1, c1;

    printf("\nDigite 0 quando desejar encerrar\n\n");
    printf("Informe A: ");
    scanf("%d", &a);
    printf("Informe B: ");
    scanf("%d", &b);
    printf("Informe C: ");
    scanf("%d", &c);

    a1 = a, b1 = b, c1 = c;
    mmc = 1;
    div = 2;

    while(a != 0 && b != 0 && c != 0){

        while(a != 1 || b != 1 || c != 1){

            if(a % div == 0 || b % div == 0 || c % div == 0){
                mmc = mmc * div;
            }else{
                div = div + 1;    
            }
            
            if(a % div == 0){
                a = a / div;
                printf("\n%d\n", a);
                printf("%d\n", (a % div));
            }
            if((b % div) == 0){
                b = b / div;
                printf("\n%d\n", b);
                printf("%d\n", (b % div));
            }
            if((c % div) == 0){
                c = c / div;
                printf("\n%d\n", c);
                printf("%d\n", (c % div));
            }
        }

        printf("\n\nMMC(%d, %d, %d) == %d\n\n", a1, b1, c1, mmc);

        printf("Informe A: ");
        scanf("%d", &a);
        printf("Informe B: ");
        scanf("%d", &b);
        printf("Informe C: ");
        scanf("%d", &c);

        a1 = a, b1 = b, c1 = c;
        mmc = 1;
        div = 2;
            
    }
    return 0;
}