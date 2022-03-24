#include <stdio.h>

int main(){
    char string[100];
    char maius[100];
    char minus[100];
    int i = 0;
    FILE * fp;
    fp=fopen("LS0x01.txt", "r");
    
    fscanf(fp, "%s", string);
    fclose(fp);

    while(string[i] != '\0'){
        if(string[i] >= 97 && string[i] <= 122){
            maius[i] = string[i] - 32;
        }else{
            maius[i] = string[i];
        }
        if(string[i] >= 65 && string[i] <= 90){
            minus[i] = string[i] + 32;
        }else{
            minus[i] = string[i];
        }
        i++;
    }

    printf("Minusculo: %s\n", minus);
    printf("Maiusculo: %s\n", maius);

    return 0;
}