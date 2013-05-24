#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "getnum.h"

void Menu (TipoDatos * dato,TipoFlag Flags);
void PedidoDimenciones(TipoDatos * dato);

void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags);
void printerror(int ind);
int validFileName(char * nombrefile);
void imprimeTablero(TipoTablero * tablero);
void imprimeMenu(int menu);

