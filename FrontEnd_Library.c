#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tilesBack.h"
#include "getnum.h"

void imprimeTablero(TipoTablero * tablero);

int main(void)
{
	srand(time(NULL));
	int aux, a, b, respuesta;
	TipoDatos edato;
	TipoDatos * dato = &edato;
	dato->nivel = 3;
	(dato->tablero).dim.filas = 12;
	(dato->tablero).dim.columnas = 17;
	(dato->tablero).c_habilidades.c_martillazos = 1;
	(dato->tablero).c_habilidades.c_hileras = 1;
	(dato->tablero).c_habilidades.c_columnas = 1;
	aux = generarTablero(dato);
	while(1)
	{
		putchar('\n');
		imprimeTablero(&(dato->tablero));
		a = getint("fila: ");
		b = getint("columna: ");
		respuesta = eliminar(&(dato->tablero), a, b);
		printf("Azulejos destruidos = %d\n", respuesta);
		gravedad(&(dato->tablero));
		nullCols(&(dato->tablero));
		getchar();
	}
	liberarMatriz(&(dato->tablero));
}


/*
Trabajamos con matrices tipo C/S (columna x filas)
*/
void imprimeTablero(TipoTablero * tablero)
{
	int i, j, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	for(i=-1; i<filas; i++)
	{
		printf(" ");
		for(j=-1; j<columnas; j++)
		{
			if(i==-1 && j>=0)
				printf("%-2d ", j);
			else if(j==-1 && i>=0)
				printf("%2d  ", i);
			else if(j>=0 && i>=0)
			{
				if((tablero->matriz)[j][i] != 0  && (tablero->matriz)[j][i]!='0')
                    printf("%c  ", (tablero->matriz)[j][i]);
				else
					printf("   ");
			}
			else
				printf("    ");
		}
		putchar('\n');
	}
}
