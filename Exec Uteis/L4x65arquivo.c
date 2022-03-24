#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float calcA(int cont, float xy, float x, float y, float x2);
float calcB(int cont, float x, float y, float x2);
float calcR(int cont, float xy, float x, float y, float x2, float y2);
//float somatorio(float res, float var);

void main(){
    float x, y, Sx, Sy, Sxy, Sx2, Sy2;
    int n = -1; 
    Sx = Sy = Sxy = Sx2 = Sy2 = 0;
    
    FILE * fp;
    fp=fopen("L4x65coord.txt", "r");

    while(x != 0 || y != 0){
        fscanf(fp, "%f %f", &x, &y);
        Sx = Sx + x;   //Sx = somatorio(Sx, x);
        Sy = Sy + y;   //Sx = somatorio(Sy, y);
        Sxy = Sxy + x*y;    //Sx = somatorio(Sxy, x*y);
        Sx2 = Sx2 + x*x;    //Sx2 = somatorio(Sx2, x*x);
        Sy2 = Sy2 + y*y;    //Sy2 = somatorio(Sy2, y*y);
        n = n + 1;
    }
    fclose(fp);

    printf("Valor obtido para o somatorio de X = %.2f\n", Sx);
    printf("Valor obtido para o somatorio de Y = %.2f\n", Sy);  
    printf("Valor obtido para o somatorio de X*Y = %.2f\n", Sxy); 
    printf("Valor obtido para o somatorio do quadarado de X = %.2f\n", Sx2); 
    printf("Valor obtido para o somatorio do quadrado de Y = %.2f\n", Sy2); 
    printf("Valor de n = %d\n", n);

    if((n*Sx2 - Sx*Sx) != 0){
        printf("O valor para A = %f\n", calcA(n, Sxy, Sx, Sy, Sx2));
        printf("O valor para B = %f\n", calcB(n, Sx, Sy, Sx2));
        printf("O valor para R = %f\n", calcR(n, Sxy, Sx, Sy, Sx2, Sy2));
    }else{
        printf("Nao foi possivel determinar A, B e R pois foi uma divisao por 0\n");
    }
}

float calcA(int cont, float xy, float x, float y, float x2){
    float a;
    a = (cont*xy - x*y) / (cont*x2 - x*x);
    return (a); 
}

float calcB(int cont, float x, float y, float x2){
    float b;
    b = (y*x2 - x*y) / (cont*x2 - x*x);
    return (b);
}

float calcR(int cont, float xy, float x, float y, float x2, float y2){
    float r, num, den1, den2, den;
    num = (cont*xy) - (x*y); 
    den1 = sqrtf((cont*x2) - (x*x));
    den2 = sqrtf((cont*y2) - (y*y));
    den = den1 * den2;
    r = num / den;
    return (r);
}

/*
float somatorio(float res, float var){
    resp = 0;
    resp = res + var;
    return (resp);
}
*/