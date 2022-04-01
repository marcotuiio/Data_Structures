#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system.h"
#include "files.h"
#include "list.h"
#include "svg.h"
#include "geo.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h"
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
    if (geoFile == NULL){
        printf("Geo File NULO\n");
        return;
    }

    buildGeometricForms(geoFile);

    //char *aux_svg = makePathSvgFile(param);
    //printf("path svg = %s\n", aux_svg);

}