#ifndef SYSTEM_H
#define SYSTEM_H

typedef void* Parameters;

Parameters *createParameters();

Parameters *setParameters(int argc, char** argv, Parameters p);

char *makePathGeoFile(Parameters p);

#endif