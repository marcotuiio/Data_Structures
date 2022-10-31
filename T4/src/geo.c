#include "geo.h"
#include "infos.h"

void readGeo(char *bedGeo, Digraph d) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];
    void* details = createDetails();
    double x, y, w, h;
    char cep[50], sw[10], cfill[15], cstrk[15];    

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "q")) {
            fscanf(geo, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);

            InfoNode new_quadra = createInfoNode(cep, x, y, w, h, details);

        } else if (!strcmp(tipo, "cq")) {
            fscanf(geo, "%s %s %s", sw, cfill, cstrk);

            setSW(details, sw);
            setCFill(details, cfill);
            setCStrk(details, cstrk);
        }
        strcpy(tipo, " ");
    }
    fclose(geo);
}

FILE *openGeo(char *bedGeo) {
    FILE *geo = fopen(bedGeo, "r");
    if (!geo) {
        printf("ERRO NA CRIAÇÃO DO GEO\n");
        exit(1);
    }
    return geo;
}