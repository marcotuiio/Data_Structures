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

    Parameters param = createParameters(argc, argv);

    char *pathGeo = makePathGeoFile(param);

    FILE *geoFile = loadFile(pathGeo);

    if (geoFile == NULL) {
        printf("Geo File NULO\n");
        return;
    }

    char *outputDir = getOutputDir(param);
    printf("output: %s\n", outputDir);

    buildGeometricForms(geoFile, outputDir);
}