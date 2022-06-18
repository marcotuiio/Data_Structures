#include "system.h"

#include "paths.h"

struct checks {
    bool readbed;
    bool readgeo;
    bool readbsd;
    bool readqry;
};
typedef struct checks Sauron;

void readParam(int argc, char** argv, Paths paths, Controller ctrl) {
    Sauron* help = ctrl;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {  // path - diretŕoio base de entrada (BED)
            i++;
            char* bed = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(bed, argv[i]);
            help->readbed = true;

            bed = fixDir(bed);

            setBed(paths, bed);

        } else if (!strcmp(argv[i], "-f")) {  // arq.geo
            i++;
            char* geofull = calloc(strlen(argv[i]) + 1, sizeof(char));
            char* geoarq = calloc(strlen(argv[i]) + 1, sizeof(char));
            char* geoname = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(geofull, argv[i]);
            help->readgeo = true;

            fixDoc(geofull, geoname);

            strcpy(geoarq, geoname);
            strcat(geoarq, ".geo");
            setGeoArq(paths, geoarq);
            setGeoName(paths, geoname);
            free(geofull);

        } else if (!strcmp(argv[i], "-o")) {  // path - diretório base de saída (BSD)
            i++;
            char* bsd = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(bsd, argv[i]);
            help->readbsd = true;

            bsd = fixDir(bsd);

            setBsd(paths, bsd);

        } else if (!strcmp(argv[i], "-q")) {  // pasta1/pasta2/arq.qry
            i++;
            char* qryarq = calloc(strlen(argv[i]) + 1, sizeof(char));
            char* qryname = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(qryarq, argv[i]);
            help->readqry = true;

            fixDoc(qryarq, qryname);

            setQryArq(paths, qryarq);
            setQryName(paths, qryname);
        }
    }

    if (help->readbed && help->readgeo) {  // bed/arq.geo
        char* bedgeo = calloc(strlen(getBed(paths)) + strlen(getGeoArq(paths)) + 1, sizeof(char));
        strcpy(bedgeo, getBed(paths));
        strcat(bedgeo, getGeoArq(paths));

        setBedGeo(paths, bedgeo);
    }

    if (help->readbed && help->readqry) {  // bed/arq.qry
        char* bedqry = calloc(strlen(getBed(paths)) + strlen(getQryArq(paths)) + 1, sizeof(char));
        strcpy(bedqry, getBed(paths));
        strcat(bedqry, getQryArq(paths));

        setBedQry(paths, bedqry);
    }

    if (help->readbsd && help->readgeo) {  // bsd/geoname.svg
        char* bsdgeosvg = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + 5, sizeof(char));
        strcpy(bsdgeosvg, getBsd(paths));
        strcat(bsdgeosvg, getGeoName(paths));
        strcat(bsdgeosvg, ".svg");

        setBsdGeoSvg(paths, bsdgeosvg);
    }

    if (help->readbsd && help->readqry) {  // bsd/geoname_qryname.svg and bsd/geoname_qryname.txt
        char* bsdgeoqrysvg = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + strlen(getQryName(paths)) + 10, sizeof(char));
        char* bsdgeoqrytxt = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + strlen(getQryName(paths)) + 10, sizeof(char));
        strcpy(bsdgeoqrysvg, getBsd(paths));
        strcat(bsdgeoqrysvg, getGeoName(paths));
        strcat(bsdgeoqrysvg, "_");
        strcat(bsdgeoqrysvg, getQryName(paths));
        strcpy(bsdgeoqrytxt, bsdgeoqrysvg);

        strcat(bsdgeoqrysvg, ".svg");
        strcat(bsdgeoqrytxt, ".txt");

        setBsdGeoQrySvg(paths, bsdgeoqrysvg);
        setBsdGeoQryTxt(paths, bsdgeoqrytxt);
    }
}

Controller createController() {
    Sauron* help = calloc(1, sizeof(Sauron));

    help->readbed = false;
    help->readbsd = false;
    help->readgeo = false;
    help->readqry = false;

    return help;
}

bool checkBED(Controller ctrl) {
    Sauron* help = ctrl;

    return help->readbed;
}

bool checkBSD(Controller ctrl) {
    Sauron* help = ctrl;

    return help->readbsd;
}

bool checkGEO(Controller ctrl) {
    Sauron* help = ctrl;

    return help->readgeo;
}

bool checkQRY(Controller ctrl) {
    Sauron* help = ctrl;

    return help->readqry;
}

void freeCtrl(Controller ctrl) {
    Sauron* help = ctrl;

    free(help);
}