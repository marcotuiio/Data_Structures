#include "geo.h"

#include "avl_tree.h"
#include "infos.h"

void readGeo(char *bedGeo, Avl t) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];
    void *details = createDetails();
    double x, y, w, h;
    char cep[30], sw[10], cfill[15], cstrk[15];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "q")) {
            fscanf(geo, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);

            InfoAvl new_quadra = createInfoAvl(cep, x, y, w, h, details);
            insertAVL(t, new_quadra, x, y);

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
    printf("bedGeo: %s\n", bedGeo);
    if (!geo) {
        printf("ERRO NA CRIAÇÃO DO GEO\n");
        exit(1);
    }
    return geo;
}