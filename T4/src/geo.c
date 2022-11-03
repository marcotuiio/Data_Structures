#include "geo.h"

#include "infos.h"
#include "rb_tree.h"

void readGeo(char *bedGeo, Rb t) {
    char *auxGeo = calloc(1, strlen(bedGeo) + 1);
    strcpy(auxGeo, bedGeo);
    int nCQ = countCQ(auxGeo);
    
    FILE *geo = openGeo(bedGeo);
    char tipo[5];
    void **details = calloc(nCQ, sizeof(void *));
    int nDetails = 0;
    double x, y, w, h;
    char cep[30], sw[10], cfill[15], cstrk[15];
    int i = 0;

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "q")) {
            fscanf(geo, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);

            InfoRb new_quadra = createInfoRb(cep, x, y, w, h, details[nDetails - 1]);
            insertRB(t, x, y, new_quadra);
            i++;

        } else if (!strcmp(tipo, "cq")) {
            fscanf(geo, "%s %s %s", sw, cfill, cstrk);
            details[nDetails] = createDetails(sw, cfill, cstrk);
            nDetails++;
        }
        strcpy(tipo, " ");
    }
    fclose(geo);
    free(auxGeo);
    setDetailsRB(t, details, nCQ);
}

FILE *openGeo(char *bedGeo) {
    FILE *geo = fopen(bedGeo, "r");
    if (!geo) {
        printf("ERRO NA CRIAÇÃO DO GEO\n");
        exit(1);
    }
    return geo;
}

int countCQ(char *bedGeoAux) {
    FILE *geoAux = fopen(bedGeoAux, "r");
    char tipo[50];
    int nCQ = 0;
    if (!geoAux) {
        printf("ERRO NA CRIAÇÃO DO GEO AUXILIAR\n");
        exit(1);
    }

    while (!feof(geoAux)) {
        fscanf(geoAux, "%s", tipo);
        if (!strcmp(tipo, "cq")) {
            nCQ++;
        }
    }
    fclose(geoAux);
    return nCQ;
}