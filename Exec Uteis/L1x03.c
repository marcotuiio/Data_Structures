#include <stdio.h>
        
/*    int main(){
    float F, C;
    F = 50;

    while(F <= 150){
        C = (5*F - 32*5) / 9;
        printf("%.1f F === %.1f C\n", F, C);
        F = F + 1;
    }
    return 0;
   }  
*/   
    
int main(){
    float F, C, K;   

    while(F >= -460){
    printf("Informe uma temperatura em FAHRENHEIT para converter em Celsius e em Kelvin: ");
    scanf("%f", &F);


    C = (5*F - 32*5) / 9;
    K = C + 273;

    printf("%.1f F === %.1f C === %.1f K", F, C, K);
    }

    return 0;
}