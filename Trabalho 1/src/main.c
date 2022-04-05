#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"
#include "files.h"
#include "geo.h"
#include "line.h"
#include "list.h"
#include "rectangle.h"
#include "svg.h"
#include "system.h"
#include "text.h"

void main(int argc, char **argv) {
    char var[100];
    printf("main1\n");
    Parameters param = createParameters(argc, argv);

    printf("main2\n");
    char *pathGeo = makePathGeoFile(param);

    printf("main3\n");
    FILE *geoFile = loadFile(pathGeo);

    printf("main4\n");
    if (geoFile == NULL) {
        printf("Geo File NULO\n");
        return;
    }

    char *outputDir = getOutputDir(param);

    buildGeometricForms(geoFile, outputDir);
}