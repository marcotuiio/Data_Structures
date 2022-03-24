#include <stdio.h>

int main(){
    char ascii;
    ascii = 33;

    while(ascii < 127){
        printf("%c\n", ascii);
    ascii++;
    }

    return 0;
}