#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * Tratamentos dos paramêtros de entrada , via argc e argv
 * Leitura dos dados, e atribuição dos determinados diretórios
*/

typedef void* Parameters;

Parameters *createParameters();

Parameters *setParameters(int argc, char** argv, Parameters p);

char *getOutputDir(Parameters p);

char *makePathGeoFile(Parameters p);

#endif