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
#define VALIDCHAR(c)			(isalnum(c) || c =='_' || c=='-')
#define DIMCHECK(filas,cols)		((filas) >= 3 && (cols) >=3 && (cols) <= MAX_COL && (filas) <= MAX_FIL) ? ON:OFF
#define NIVCHECK(nivel,filas,columnas)	((nivel) >= 2 && (nivel) <= NIVEL_MAX(filas*columnas)) ? ON:OFF
#define NIVEL_MAX(azulejos)		((8 > ((azulejos)/2)) ? ((azulejos)/2):8)			

//INDICES
#define BITACORA	0 
#define PROX_NIVEL	1
#define FIN_JUEGO	2
#define FIN_APLICACION	3

enum estados {ON=0,OFF};
typedef enum estados TipoEstado;
typedef TipoEstado TipoFlag[4]; //1er FLAG: BITACORA, 2do FLAG: NEXT LEVEL, 3er FLAG: GAME OVER, 4to FLAG: END APP

void Menu (TipoDatos * dato,TipoFlag Flags);
void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags);
void resultadoFindelNivel(TipoDatos * dato,TipoFlag Flags);

void PedidoDimenciones(TipoDatos * dato);
void PedidoNivel(TipoDatos * dato);
int validFileName(char * nombrefile);
void inputString(char * string);

void imprimeTablero(TipoTablero * tablero);
void imprimirEstado(TipoDatos * dato);
void printerror(int ind);

#endif
