#include "libs.h"

#include "geo.h"
#include "qry.h"
#include "system.h"

int main(int argc, char **argv) {
    FILE *qryFile;

    Parameters param = createParameters(argc, argv);

    char *pathGeo = makePathGeoFile(param);

    FILE *geoFile = loadFile(pathGeo);

    if (geoFile == NULL) {
        printf("Geo File NULO\n");
        return 0;
    }

    char *pathqryoriginal = calloc(strlen(getQryPath(param)) + 5, sizeof(char));
    strcpy(pathqryoriginal, getQryPath(param));    
    
    char *outputDir = getOutputDir(param);

    if (qryExiste(param) == 1) {
        char *pathQry = makePathQryFile(param, pathqryoriginal);
        int size = strlen(pathQry);
        char *path_aux = calloc(1, size + 1);
        strcpy(path_aux, pathQry);
        qryFile = loadFile(pathQry);
        // printf("out %s\n", outputDir);

        int q_size = countInp(path_aux);
        // printf("SIZE QUEUE %d\n", q_size);

        buildGeometricForms(geoFile, outputDir, qryFile, 1, q_size);
        free(path_aux);
        free(pathQry);

    } else {
        buildGeometricForms(geoFile, outputDir, NULL, 0, 0);
    }

    freeParam(param);
    free(pathGeo);
    free(pathqryoriginal);
    //free(outputDir);

    printf("\n--- SUCCESS ---\n");

    return 0;
}
