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
#define FIN_APLICACION			3
#define	UNDO				4
#define LOAD				5

typedef struct 
{
    FILE * archivo_bitacora;
    char nombre_bitacora[MAX_LONG_FILE+4];
} TipoBitacora;

enum estados {OFF=0,ON};
typedef enum estados TipoEstado;
typedef TipoEstado TipoFlag[6];

/* Pide informacion al usuario a traves de una interface grafica para setear los datos iniciales del juego */
void Menu (TipoDatos * dato,TipoFlag Flags,TipoBitacora * bitacora );

/* Llama a funciones del BackEnd en funcion a la accion que ingresa el usuario */
void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags,TipoBitacora  bitacora,TipoDatos * aux_dato);

/* Imprime en pantalla el puntaje final obtenido */
void resultadoFindelNivel(TipoDatos * dato,TipoFlag Flags);

/* Pide al usuario que ingrese las dimensiones de la matriz y setea las variables correspondientes */
void PedidoDimenciones(TipoDatos * dato); 

/* Pide al usuario que ingrese el nivel hasta el que desea jugar y setea las variables correspondientes */
void PedidoNivel(TipoDatos * dato);

/* Pide al usuario un nombre valido para un archivo y lo almacena en nombrefile */
void PedirNombreValido(char * nombrefile); 

/* Valida que nombrefile sea un nombre de archivo valido */
int validFileName(char * nombrefile);

/* Quita '\n' final de un string */
void inputString(char * string);

/* Genera un archivo de texto con la copia del contenido arch_origen */ 
TipoEstado SaveBitacora(char * nombrefile,FILE * arch_origen);

/* Carga el archivo nombrefile con extension txt (si existe) modificando archivo_bitacora */
TipoEstado LoadBitacora(char * nombrefile,FILE ** archivo_bitacora); 

/* Imprime la matriz de juego */
void imprimeTablero(TipoTablero * tablero);

/* Imprime la cantidad actual de habilidades y el puntaje obtenido hasta el momento */
void imprimirEstado(TipoDatos * dato);

/* Imprime un mensaje correspondiente al error que se le pasa por parametro */
void printerror(int ind);

/* Imprime una pantalla explicando como se juega el juego y cuales son las dimensiones maximas que una matriz puede tener */
void instrucciones(void);

/* Guarda la partida que esta en juego */
int save(TipoDatos * dato, TipoEstado flagBitacora, char * nombre);

/* Carga un partida anteriormente salvada, devuelve 1 si no hubo error y un numero negativo si lo hubo  */
int load(TipoDatos * dato, TipoEstado * flagBitacora, char * nombre);

/* Guarda en archivo_bitacora la accion ejecutada, devuelve 1 si no hubo error y un numero negativo si lo hubo */
int GuardarAccionBitacora(FILE * archivo_bitacora,char * operacion, TipoEstado prox_nivel, int puntaje,int cant_azulejos);

/* Guarda en archivo_bitacora el tablero de juego, devuelve 1 si no hubo error y un numero negativo si lo hubo */
int GuardarMATBitacora(TipoTablero * tablero,FILE * archivo_bitacora);

/* Imprime un char en color en la STDOUT*/
void imprimirColor(char letra);

/* Compara el string file con el nombre de la bitacora para no sobreescribirla, devuelve 0 si son iguales y 1 sino */
int compBit_File(char * bit ,char *file);

#endif
