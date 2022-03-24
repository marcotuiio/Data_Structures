#include <stdio.h>
int main (){
    int TF;

    printf("Digite 1 para calcular ENERGIA CINETICA, 2 para ENERGIA POTENCIAL GRAVITACIONAL e 3 para ENERGIA POTENCIAL ELASTICA: ");
    scanf("%d", &TF);

      if(TF < 1 || TF > 3){
          printf("VALOR INVALIDO");
          return 0;
      }
        
      if(TF == 1){  
           float massa, velocidade, resultadoC;
 
           printf("Informe a massa em KG: ");
           scanf("%f", &massa);
           printf("Informe a velocidade em m/s: ");
           scanf("%f", &velocidade);

           resultadoC = massa * (velocidade * velocidade) / 2;

           printf("Sua energia cinetica e de %.1f Joules\n", resultadoC);

      }else if(TF == 2){
           float massa, gravidade, altura, resultadoPG;

           printf("Informe a massa em KG: ");
           scanf("%f", &massa);
           printf("Informe a gravidade: ");
           scanf("%f", &gravidade);
           printf("Informe a altura em metros: ");
           scanf("%f", &altura);

           resultadoPG = massa * gravidade * altura;

           printf("Sua energia potencial gravitacional e de %.1f Joules\n", resultadoPG);

      }else{
           float constante, deformacao, resultadoE;

           printf("Informe a constante elastica em N/m: ");
           scanf("%f", &constante);
           printf("Informe a deformacao do objeto em metros: ");
           scanf("%f", &deformacao);
 
           resultadoE = constante * (deformacao * deformacao) / 2;

           printf("Sua energia potencial elastica e de %.1f", resultadoE);

    }

    return 0;
}