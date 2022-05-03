#include "libs.h"

#ifndef PATHS_H
#define PATHS_H

Paths createAllPaths();

char* prepareDir(char* dir);

void prepareDoc(char* asread, char* onlyname);

void setBed(Paths path, char* bed);

char* getBed(Paths path);

void setBsd(Paths path, char* bsd);

char* getBsd(Paths path);

void setBedGeo(Paths path, char* bedgeo);

char* getBedGeo(Paths path);

void setGeoArq(Paths path, char* geoarq);

char* getGeoArq(Paths path);

void setGeoName(Paths path, char* geoname);

char* getGeoName(Paths path);

void setBedQry(Paths path, char* bedqry);

char* getBedQry(Paths path);

void setQryArq(Paths path, char* qryarq);

char* getQryArq(Paths path);

void setQryName(Paths path, char* qryname);

char* getQryName(Paths path);

void setBsdGeoSvg(Paths path, char* bsdgeosvg);

char* getBsdGeoSvg(Paths path);

void setBsdGeoQrySvg(Paths path, char* bsdgeoqrysvg);

char* getBsdGeoQrySvg(Paths path);

void setBsdGeoQryTxt(Paths path, char* bsdgeoqrytxt);

char* getBsdGeoQryTxt(Paths path);

void freePaths(Paths path);

#endif
