#include "system.h"

#include "paths.h"

void readParam(int argc, char** argv, void* paths) {
    bool readbed = false;
    bool readgeo = false;
    bool readbsd = false;
    bool readqry = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {  // path - diretŕoio base de entrada (BED)
            i++;
            char* bed = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(bed, argv[i]);
            readbed = true;

            bed = prepareDir(bed);

            setBed(paths, bed);

        } else if (!strcmp(argv[i], "-f")) {  // arq.geo
            i++;
            char* geofull = calloc(strlen(argv[i]) + 1, sizeof(char));
            char* geoarq = calloc(strlen(argv[i]) + 1, sizeof(char));
            char* geoname = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(geofull, argv[i]);
            readgeo = true;

            prepareDoc(geofull, geoname);

            strcpy(geoarq, geoname);
            strcat(geoarq, ".geo");
            setGeoArq(paths, geoarq);
            setGeoName(paths, geoname);
            free(geofull);

        } else if (!strcmp(argv[i], "-o")) {  // path - diretório base de saída (BSD)
            i++;
            char* bsd = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(bsd, argv[i]);
            readbsd = true;

            bsd = prepareDir(bsd);

            setBsd(paths, bsd);

        } else if (!strcmp(argv[i], "-q")) {  // pasta1/pasta2/arq.qry
            i++;
            char* qryarq = calloc(strlen(argv[i]) + 1, sizeof(char));
            char* qryname = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(qryarq, argv[i]);
            readqry = true;

            setQryArq(paths, qryarq);

            strcpy(qryname, qryarq);
            setQryName(paths, qryname);
            prepareDoc(qryarq, qryname);
            free(qryname);
        }
    }

    if (readbed && readgeo) {  // bed/arq.geo
        char* bedgeo = calloc(strlen(getBed(paths)) + strlen(getGeoArq(paths)) + 1, sizeof(char));
        strcpy(bedgeo, getBed(paths));
        strcat(bedgeo, getGeoArq(paths));

        setBedGeo(paths, bedgeo);
    }

    if (readbed && readqry) {  // bed/arq.qry
        char* bedqry = calloc(strlen(getBed(paths)) + strlen(getQryArq(paths)) + 1, sizeof(char));
        strcpy(bedqry, getBed(paths));
        strcat(bedqry, getQryArq(paths));

        setBedQry(paths, bedqry);
    }

    if (readbsd && readgeo) {  // bsd/geoname.svg
        char* bsdgeosvg = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + 5, sizeof(char));
        strcpy(bsdgeosvg, getBsd(paths));
        strcat(bsdgeosvg, getGeoName(paths));
        strcat(bsdgeosvg, ".svg");

        setBsdGeoSvg(paths, bsdgeosvg);
    }

    if (readbsd && readqry) {  // bsd/geoname_qryname.svg and bsd/geoname_qryname.txt
        char* bsdgeoqrysvg = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + strlen(getQryName(paths)) + 6, sizeof(char));
        char* bsdgeoqrytxt = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + strlen(getQryName(paths)) + 6, sizeof(char));
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