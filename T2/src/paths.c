#include "paths.h"

struct param {
    char* bed;           // path - diretŕoio base de entrada (BED)
    char* bsd;           // path - diretŕoio base de saída (BSD)
    char* bedgeo;        // arq.geo com BED
    char* geoarq;        // arq.geo
    char* geoname;       // only name (no .geo)
    char* bedqry;        // arq.qry com BED
    char* qryarq;        // testes/arq.qry
    char* qryname;       // only name (no .qry)
    char* bsdgeosvg;     // bsd/nomegeo.svg
    char* bsdgeoqrysvg;  // nomegeo_nomeqry.svg
    char* bsdgeoqrytxt;  // nomegeo_nomeqry.txt
};
typedef struct param AllPaths;

Paths createAllPaths() {
    AllPaths* aux = calloc(1, sizeof(AllPaths));
    return aux;
}

char* prepareDir(char* dir) {
    if (dir[strlen(dir) - 1] != '/') {
        dir = realloc(dir, strlen(dir) + 2);
        strcat(dir, "/");
    }
    return dir;  // padrao de sempre ter barra no fim
}

void prepareDoc(char* asread, char* onlyname) {
    int index = 0, pos = 0;
    bool found = false;

    for (int i = strlen(asread) - 1; i >= 0; i--) {
        if (asread[i] == '/') {
            index = i;
            found = true;
            break;
        }
    }

    if (found) {
        for (int i = index + 1; i < strlen(asread); i++) {
            if (asread[i] == '.') {
                onlyname[pos] = '\0';
                break;
            } else {
                onlyname[pos] = asread[i];
                pos++;
            }
        }
    } else {
        strcpy(onlyname, asread);
        for (int i = 0; i < strlen(onlyname); i++) {
            if (onlyname[i] == '.') {
                onlyname[i] = '\0';
            }
        }
    }
}

void setBed(Paths path, char* bed) {
    AllPaths* paths = path;
    paths->bed = bed;
}

char* getBed(Paths path) {
    AllPaths* paths = path;
    return paths->bed;
}

void setBsd(Paths path, char* bsd) {
    AllPaths* paths = path;
    paths->bsd = bsd;
}

char* getBsd(Paths path) {
    AllPaths* paths = path;
    return paths->bsd;
}

void setBedGeo(Paths path, char* bedgeo) {
    AllPaths* paths = path;
    paths->bedgeo = bedgeo;
}

char* getBedGeo(Paths path) {
    AllPaths* paths = path;
    return paths->bedgeo;
}

void setGeoArq(Paths path, char* geoarq) {
    AllPaths* paths = path;
    paths->geoarq = geoarq;
}

char* getGeoArq(Paths path) {
    AllPaths* paths = path;
    return paths->geoarq;
}

void setGeoName(Paths path, char* geoname) {
    AllPaths* paths = path;
    paths->geoname = geoname;
}

char* getGeoName(Paths path) {
    AllPaths* paths = path;
    return paths->geoname;
}

void setBedQry(Paths path, char* bedqry) {
    AllPaths* paths = path;
    paths->bedqry = bedqry;
}

char* getBedQry(Paths path) {
    AllPaths* paths = path;
    return paths->bedqry;
}

void setQryArq(Paths path, char* qryarq) {
    AllPaths* paths = path;
    paths->qryarq = qryarq;
}

char* getQryArq(Paths path) {
    AllPaths* paths = path;
    return paths->qryarq;
}

void setQryName(Paths path, char* qryname) {
    AllPaths* paths = path;
    char *index = strrchr(paths->qryarq, '/');
    index++;
    char *aux = calloc(1, sizeof(index) + 24);
    strcpy(aux, index);
    char *name;
    name = strtok(aux, ".qry");
    paths->qryname = name;
}

char* getQryName(Paths path) {
    AllPaths* paths = path;
    return paths->qryname;
}

void setBsdGeoSvg(Paths path, char* bsdgeosvg) {
    AllPaths* paths = path;
    paths->bsdgeosvg = bsdgeosvg;
}

char* getBsdGeoSvg(Paths path) {
    AllPaths* paths = path;
    return paths->bsdgeosvg;
}

void setBsdGeoQrySvg(Paths path, char* bsdgeoqrysvg) {
    AllPaths* paths = path;
    paths->bsdgeoqrysvg = bsdgeoqrysvg;
}

char* getBsdGeoQrySvg(Paths path) {
    AllPaths* paths = path;
    return paths->bsdgeoqrysvg;
}

void setBsdGeoQryTxt(Paths path, char* bsdgeoqrytxt) {
    AllPaths* paths = path;
    paths->bsdgeoqrytxt = bsdgeoqrytxt;
}

char* getBsdGeoQryTxt(Paths path) {
    AllPaths* paths = path;
    return paths->bsdgeoqrytxt;
}

void freePaths(Paths path) {
    AllPaths* paths = path;

    free(paths->bed);
    free(paths->bsd);
    free(paths->bedgeo);
    free(paths->bedqry);
    free(paths->geoname);
    free(paths->geoarq);
    free(paths->qryarq);
    free(paths->bsdgeoqrysvg);
    free(paths->bsdgeoqrytxt);
    free(paths->bsdgeosvg);
    free(paths);
}
