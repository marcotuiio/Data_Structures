#include "paths.h"

struct param {
    char* bed;           // diretório base de entrada (BED)
    char* bsd;           // diretório base de saída (BSD)
    char* bedgeo;        // bed/arq.geo
    char* geoarq;        // arq.geo
    char* geoname;       // only name (no .geo)
    char* bedvia;        // bed/arq.via
    char* viaarq;        // arq.via
    char* bedqry;        // bed/pasta/arq.qry
    char* qryarq;        // pasta/arq.qry
    char* qryname;       // only name (no .qry)
    char* bsdgeosvg;     // bsd/nomegeo.svg
    char* bsdgeodot;     // bsd/nomegeo.dot
    char* bsdgeoqrysvg;  // bsd/nomegeo_nomeqry.svg
    char* bsdgeoqrytxt;  // bsd/nomegeo_nomeqry.txt
    char* bsdgeoqrydot;  // bsd/nomegeo_nomeqry.dot
};
typedef struct param AllPaths;

Paths createAllPaths() {
    AllPaths* aux = calloc(1, sizeof(AllPaths));
    return aux;
}

char* fixDir(char* dir) {
    if (dir[strlen(dir) - 1] != '/') {
        dir = realloc(dir, strlen(dir) + 2);
        strcat(dir, "/");
    }
    return dir;  // manter / no final dos diretorios
}

void fixDoc(char* from_param, char* arq_name) {
    char* index = strrchr(from_param, '/');

    if (index) {
        index++;
        char* tok = strtok(index, ".");
        strcpy(arq_name, tok);

    } else {
        strcpy(arq_name, from_param);
        strtok(arq_name, ".");
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

void setBedVia(Paths path, char* bedvia) {
    AllPaths* paths = path;
    paths->bedvia = bedvia;
}

char* getBedVia(Paths path) {
    AllPaths* paths = path;
    return paths->bedvia;
}

void setViaArq(Paths path, char* viaarq) {
    AllPaths* paths = path;
    paths->viaarq = viaarq;
}

char* getViaArq(Paths path) {
    AllPaths* paths = path;
    return paths->viaarq;
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
    strcat(qryarq, ".qry");
    paths->qryarq = qryarq;
}

char* getQryArq(Paths path) {
    AllPaths* paths = path;
    return paths->qryarq;
}

void setQryName(Paths path, char* qryname) {
    AllPaths* paths = path;
    paths->qryname = qryname;
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

void setBsdGeoDot(Paths path, char* bsdgeodot) {
    AllPaths* paths = path;
    paths->bsdgeodot = bsdgeodot;
}

char* getBsdGeoDot(Paths path) {
    AllPaths* paths = path;
    return paths->bsdgeodot;
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

void setBsdGeoQryDot(Paths path, char* bsdgeoqrydot) {
    AllPaths* paths = path;
    paths->bsdgeoqrydot = bsdgeoqrydot;
}

char* getBsdGeoQryDot(Paths path) {
    AllPaths* paths = path;
    return paths->bsdgeoqrydot;
}

void freePaths(Paths path) {
    AllPaths* paths = path;

    free(paths->bed);
    free(paths->bsd);
    free(paths->bedgeo);
    free(paths->bedqry);
    free(paths->geoname);
    free(paths->geoarq);
    free(paths->bedvia);
    free(paths->viaarq);
    free(paths->qryname);
    free(paths->qryarq);
    free(paths->bsdgeosvg);
    free(paths->bsdgeodot);
    free(paths->bsdgeoqrysvg);
    free(paths->bsdgeoqrytxt);
    free(paths->bsdgeoqrydot);
    free(paths);
}
