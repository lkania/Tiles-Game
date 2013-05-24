#ifndef tilesFront_H
#define tilesFront_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tilesBack.h"
#include "getnum.h"

//CONSTANTES
#define	MAX_LONG	30
#define MAX_COL		15
#define MAX_FIL		15

//MACROS
#define VALIDCHAR(c)		(isalnum(c) || c =='_' || c=='-')
#define	FREE_BUFFER		while(getchar()!='\n')
#define DIMCHECK(filas,cols)	(filas >= 3 && cols >=3 && cols <= MAX_COL && filas <= MAX_FIL) ? ON:OFF

//INDICES
#define BITACORA	0 
#define NEXT_LEVEL	1
#define GAME_OVER	2
#define END_APPLICATION	3

enum estados {ON=0,OFF};
typedef enum estados TipoEstado;
typedef TipoEstado TipoFlag[4]; //1er FLAG: BITACORA, 2do FLAG: NEXT LEVEL, 3er FLAG: GAME OVER, 4to FLAG: END APP

void Menu (TipoDatos * dato,TipoFlag Flags);

void PedidoDimenciones(TipoDatos * dato);
void imprimeTablero(TipoTablero * tablero);
void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags);

void printerror(int ind);
int validFileName(char * nombrefile);
void inputString(char * string);

#endif
