#include "geo.h"

#include "infos.h"
#include "rb_tree.h"

void readGeo(char *bedGeo, Rb t) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];
    double x, y, w, h;
    char cep[30], sw[10], cfill[15], cstrk[15];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "q")) {
            fscanf(geo, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);

            void *details = createDetails(sw, cfill, cstrk);
            InfoRb new_quadra = createInfoRb(cep, x, y, w, h, details);
            insertRB(t, x, y, new_quadra);

        } else if (!strcmp(tipo, "cq")) {
            fscanf(geo, "%s %s %s", sw, cfill, cstrk);
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
