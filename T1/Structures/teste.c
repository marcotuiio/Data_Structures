#include <stdio.h>

int main() {
    char test[] = "/home/marcotuiio/ED1/EDor/T1/input/g.geo";
    char info[20];
    printf("\n%s\n\n", test);
    FILE * arq = fopen(test, "r");

    while (!feof(arq)) {
        fscanf (arq, "%s", info);
        printf("%s\n", info);
    }

    FILE * arq2 = fopen("/home/marcotuiio/ED1/EDor/T1/output/teste.geo", "w");
    fprintf(arq2, "%s", info);
}