#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geo.h"
#include "system.h"
#include "qry.h"

void main(int argc, char **argv) {
    char var[100];

    Parameters param = createParameters(argc, argv);

    char *pathGeo = makePathGeoFile(param);

    FILE *geoFile = loadFile(pathGeo);

    if (geoFile == NULL) {
        printf("Geo File NULO\n");
        return;
    }

    char *outputDir = getOutputDir(param);

    buildGeometricForms(geoFile, outputDir);

    if (qryExiste(param) == 1) {
        char *pathQry = makePathQryFile(param);

        FILE *qryFile = loadFile(pathQry);

        readComands(qryFile);
    }
}