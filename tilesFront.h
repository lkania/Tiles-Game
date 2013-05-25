#ifndef tilesFront_H
#define tilesFront_H

#include "tilesBack.h"

//CONSTANTES
#define	MAX_LONG			30
#define	MIN_FIL				3
#define	MIN_COL				3
#define MAX_FIL 			15
#define MAX_COL 			15
#define	MIN_NIVEL			2
#define	MAX_NIVEL			8

//MACROS
#define VALIDCHAR(c)			(isalnum(c) || c =='_' || c=='-')
#define DIMCHECK(filas,cols)		((filas) >= MIN_FIL && (cols) >= MIN_COL && (cols) <= MAX_COL && (filas) <= MAX_FIL) ? ON:OFF
#define NIVCHECK(nivel,filas,columnas)	((nivel) >= MIN_NIVEL && (nivel) <= NIVEL_MAX(filas*columnas)) ? ON:OFF
#define NIVEL_MAX(azulejos)		((MAX_NIVEL > ((azulejos)/2)) ? ((azulejos)/2):MAX_NIVEL)			

//INDICES
#define BITACORA			0 
#define PROX_NIVEL			1
#define FIN_JUEGO			2
#define FIN_APLICACION			3

enum estados {OFF=0,ON};
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
void instrucciones(TipoFlag Flags);

#endif
