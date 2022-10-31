#include "libs.h"

#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * Tratamentos dos paramêtros de entrada , via argc e argv
 * Leitura dos dados, e atribuição dos determinados diretórios
 */

void readParam(int argc, char* argv[], Paths paths, Controller ctrl);
// Recebe os parâmetros de entrada e a media que os lê, faz o devido
// tratamento e organização desses dados

Controller createController();
bool checkBED(Controller ctrl);
bool checkBSD(Controller ctrl);
bool checkGEO(Controller ctrl);
bool checkVIA(Controller ctrl);
bool checkQRY(Controller ctrl);
void freeCtrl(Controller ctrl);
// Funções complementares que recebem dados confirmando ou não
// a leitura de determinados parâmetros para que o projeto
// possa continuar

#endif