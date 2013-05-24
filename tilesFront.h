#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "getnum.h"

#define	MAX_LONG	30
#define VALIDCHAR(c)	(isalnum(c) || c =='_' || c=='-')
#define	FREE_BUFFER	while(getchar()!='\n')
#define BITACORA 0 
#define NEXT_LEVEL 1
#define GAME_OVER 2

enum estados {ON=0,OFF};
typedef enum estados TipoEstado;
typedef TipoEstado TipoFlag[3]; //1er FLAG: BITACORA, 2do FLAG: NEXT LEVEL, 3er FLAG: GAME OVER

void Menu (TipoDatos * dato,TipoFlag Flags);
void PedidoDimenciones(TipoDatos * dato);

void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags);
void printerror(int ind);
int validFileName(char * nombrefile);
void imprimeTablero(TipoTablero * tablero);
void imprimeMenu(int menu);
