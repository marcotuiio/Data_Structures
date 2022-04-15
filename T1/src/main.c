#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geo.h"
#include "qry.h"
#include "system.h"

void main(int argc, char **argv) {
    char var[100];
    FILE *qryFile;

    Parameters param = createParameters(argc, argv);

    char *pathGeo = makePathGeoFile(param);

    FILE *geoFile = loadFile(pathGeo);

    if (geoFile == NULL) {
        printf("Geo File NULO\n");
        return;
    }

    char *outputDir = getOutputDir(param);

    if (qryExiste(param) == 1) {
        char *pathQry = makePathQryFile(param);

        qryFile = loadFile(pathQry);

        buildGeometricForms(geoFile, outputDir, qryFile, 1);

    } else {
        buildGeometricForms(geoFile, outputDir, NULL, 0);
    }

    free(param);
    free(pathGeo);
    
}
