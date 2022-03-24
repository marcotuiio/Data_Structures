#include <stdio.h>

int main(){
    int x;
   
    for(x=1000; x<=9999; x++){    
       if(x == (((x/100)+(x%100))*((x/100)+(x%100)))){ /*ex: 2045/100=20, 2045%100=45*/
         printf("%d\n", x);   
       } 
    }

    return 0;
}