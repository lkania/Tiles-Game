#ifndef tilesFront_H
#define tilesFront_H

#include "tilesBack.h"
#include <stdio.h>

//CONSTANTES
#define	MAX_LONG			30
#define	MIN_FIL				3
#define	MIN_COL				3
#define MAX_FIL 			15
#define MAX_COL 			15
#define	MIN_NIVEL			2
#define	MAX_NIVEL			8
#define	MAX_LONG_FILE			25

//MACROS
#define VALIDCHAR(c)			(isalnum(c) || c =='_' || c=='-')
#define DIMCHECK(filas,cols)		((filas) >= MIN_FIL && (cols) >= MIN_COL && (cols) <= MAX_COL && (filas) <= MAX_FIL) ? ON:OFF
#define NIVCHECK(nivel,filas,columnas)	((nivel) >= MIN_NIVEL && (nivel) <= NIVEL_MAX(filas*columnas)) ? ON:OFF
#define NIVEL_MAX(azulejos)		((MAX_NIVEL > ((azulejos)/2)) ? ((azulejos)/2):MAX_NIVEL)			

//INDICES
#define BITACORA			0 
#define PROX_NIVEL			1
#define FIN_JUEGO			2
#define FIN_APLICACION		3
#define	UNDO				4
#define LOAD                5

typedef struct {
    FILE * archivo_bitacora;
    char nombre_bitacora[MAX_LONG_FILE+4];
} TipoBitacora;


enum estados {OFF=0,ON};
typedef enum estados TipoEstado;
typedef TipoEstado TipoFlag[6];

void Menu (TipoDatos * dato,TipoFlag Flags,TipoBitacora * bitacora );  // Pide informacion al usuario a traves de interfas grafica para setear los datos iniciales del juego


void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags,TipoBitacora  bitacora,TipoDatos * aux_dato);/* Esta funcion se encaraga de llamar a funciones del back en funcion
                                                                                                      a la accion que ingresa el usuario */

void resultadoFindelNivel(TipoDatos * dato,TipoFlag Flags);

void PedidoDimenciones(TipoDatos * dato); // Pide al usuario que ingrese las dimensiones de la matriz y setea las variables correspondientes

void PedidoNivel(TipoDatos * dato);

void PedirNombreValido(char * nombrefile); 

int validFileName(char * nombrefile);

void inputString(char * string);

TipoEstado SaveBitacora(char * nombrefile,FILE * arch_origen); // Genera un archivo de texto con la copia del contenido arch_origen

TipoEstado LoadBitacora(char * nombrefile,FILE ** archivo_bitacora);// Carga el archivo nombrefile con extension txt (si existe) modificando archivo_bitacora

void imprimeTablero(TipoTablero * tablero);

void imprimirEstado(TipoDatos * dato);

void printerror(int ind);

void instrucciones(void);

int save(TipoDatos * dato, TipoEstado flagBitacora, char * nombre);

int load(TipoDatos * dato, TipoEstado * flagBitacora, char * nombre);

int GuardarAccionBitacora(FILE * archivo_bitacora,char * operacion, TipoEstado prox_nivel, int puntaje,int cant_azulejos); // Guarda en archivo_bitacora la accion ejecutada

int GuardarMATBitacora(TipoTablero * tablero,FILE * archivo_bitacora); // Guarda en archivo_bitacora el tablero de juego

void imprimirColor(char letra);

#endif
