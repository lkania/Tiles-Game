#include <stdio.h>
#include <stdlib.h>
#include "tilesBack.h"

/*
Esta es la libreria de good-engineer
*/

void Crear_Nivel(TipoDatos * dato)
{

	dato->nivel++;
	dato->puntaje=0;
	(dato->tablero).c_habilidades.c_martillazos ++;
	(dato->tablero).c_habilidades.c_hileras ++;
	(dato->tablero).c_habilidades.c_columnas ++;
	generarTablero(dato);
}

void Proc_Matriz(TipoDatos * dato)
{

	gravedad(&(dato->tablero));
	nullCols(&(dato->tablero));
	return;


}


int validFileName(char * nombrefile)
{	int i;

	for(i=0;nombrefile[i]!=0;i++)
	{
		if(!VALIDNAME(nombrefile[i]))
			return 0;
	}
		return 1;
}

int generarTablero(TipoDatos * dato)
{
	//LLAMADO A srand(time(NULL)) lo hacemos UNA sola vez, y desde el main
	int i, j, indice, nivel = dato->nivel, filas = (dato->tablero).dim.filas, columnas = (dato->tablero).dim.columnas;
	char ** tablero = malloc(columnas*sizeof(char*));
	if(tablero == NULL)
		return SIN_MEMORIA;
	for(j=0; j<columnas; j++)
	{
		tablero[j] = malloc(filas);
		if(tablero[j] == NULL)
		{
			j--;
			for(;j>=0; j--)
				free(tablero[j]);
			free(tablero);
			return SIN_MEMORIA;
		}
	}
	for(j=0; j<columnas; j++)
	{
		for(i=0; i<filas; i++)
		{
			indice = rand()%(nivel+1);
			tablero[j][i] = 'A' + indice;
		}
	}
	(dato->tablero).matriz = tablero;
	return 0;
}

 void liberarMatriz(TipoTablero * tablero)
{
	int j, columnas = (tablero->dim).columnas;
	for(j=0; j<columnas; j++)
		free((tablero->matriz)[j]);
	free(tablero->matriz);
}

 void elimAd(TipoTablero * tablero, int i, int j, char tipo, int * azulejos)
{
	if((tablero->matriz)[j][i]==tipo)
	{
		int h, k;
		(tablero->matriz)[j][i]='\0';
		(*azulejos)++;
		for(k=j-1; h<=j+1; j++)
			for(h=i-1; h<=i+1; h++)
				if(h>=0 && h<(tablero->dim).filas && k>=0 && k<(tablero->dim).columnas && (MOD(h-i)+MOD(k-j))==1 )
					elimAd(tablero, h, k, tipo, azulejos);
	}
}

int eliminar(TipoTablero * tablero, int i, int j)
{
	int azulejos=validarEliminar(tablero, i, j);
	if(azulejos == 0)
	{
		char tipo = (tablero->matriz)[j][i];
		elimAd(tablero, i, j, tipo, &azulejos);
	}
	return azulejos;
}

int martillazo(TipoTablero * tablero, int i, int j)
{
	int azulejos = validarMartillazo(tablero, i, j);
	if(azulejos == 0)
	{
		int h, k;
	    for(k=j-1; k<=j+1; k++)
		{
        	for(h=i-1; h<=i+1; h++)
			{
        	    if(h>=0 && h<(tablero->dim).filas && k>=0 && (tablero->dim).columnas && (tablero->matriz)[k][h]!=0)
				{
        	        (tablero->matriz)[k][h] = '\0';
					azulejos++;
				}
			}
		}
	}
	(tablero->c_habilidades).c_martillazos--;
	return azulejos;
}

int hilera(TipoTablero * tablero, int hilera)
{
	int azulejos = validarHilera(tablero, hilera);
	if(azulejos == 0)
	{
		int j;
    	for(j=0; j<(tablero->dim).columnas; j++)
		{
			if((tablero->matriz)[j][hilera]!=0)
			{
				(tablero->matriz)[j][hilera] = '\0';
				azulejos++;
			}
		}	
	}
	(tablero->c_habilidades).c_hileras--;
	return azulejos;
}

int columna(TipoTablero * tablero, int columna)
{
	int azulejos = validarColumna(tablero, columna);
	if(azulejos == 0)
	{
		int i;
    	for(i=0; i<(tablero->dim).filas; i++)
		{
			if((tablero->matriz)[columna][i]!=0)
			{
    	    	(tablero->matriz)[columna][i] = '\0';
				azulejos++;
			}
		}
	}
	(tablero->c_habilidades).c_columnas--;
	return azulejos;
}

 int validarEliminar(TipoTablero * tablero, int i, int j)
{
	int aux, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	char tipo;
	if(i<0 || i>=filas || j<0 || j>=columnas)
		return FUERA_RANGO;
	else if((tablero->matriz)[j][i]=='0')
			return POSICION_NULA;
	else
	{
		tipo = (tablero->matriz)[j][i];
		aux = ((i-1>=0 && (tablero->matriz)[j][i-1]==tipo)||
			(j-1>=0 && (tablero->matriz)[j-1][i]==tipo)||
			(i+1<filas && (tablero->matriz)[j][i+1]==tipo)||
			(j+1<columnas && (tablero->matriz)[j+1][i]==tipo));
		if(!aux)
			return SIN_ADYACENCIA;
	}
	return 0;
}

 int validarMartillazo(TipoTablero * tablero, int i, int j)
{
	int filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	if(i<0 || i>=filas || j<0 || j>=columnas)
		return FUERA_RANGO;
	else if((tablero->matriz)[j][i]!='0')
		return POSICION_NULA;
	else if((tablero->c_habilidades).c_martillazos < 1)
		return NO_HAB;
	return 0;
}

int validarHilera(TipoTablero * tablero, int hilera)
{
	int j, flag = 0, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	if(hilera<0 || hilera >= filas)
		return FUERA_RANGO;
	for(j=0; j<columnas && !flag; j++)
		if((tablero->matriz)[j][hilera]!='0')
			flag = 1;
	if(flag == 0)
		return HILERA_NULA;
	else if((tablero->c_habilidades).c_hileras < 1)
		return NO_HAB;
	return 0;
}

int validarColumna(TipoTablero * tablero, int columna)
{
	int i, flag = 0, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	if(columna < 0 || columna >= columnas)
		return FUERA_RANGO;
	else
		for(i=0; i<filas && !flag; i++)
			if((tablero->matriz)[columna][i]!='0')
				flag = 1;
	if(flag==0)
		return COLUMNA_NULA;
	else if((tablero->c_habilidades).c_columnas < 1)
		return NO_HAB;
	return 0;
}

 void gravedad(TipoTablero * tablero)
{
	int i, j, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	for(j=0; j<columnas; j++)
	{
		for(i=filas-1; i>=0 && (tablero->matriz)[j][i]!='0'; i--)
		{
			if((tablero->matriz)[j][i] == '\0')
			{
				decalarFils(tablero, i, j);
			}
		}
	}
}

void decalarFils(TipoTablero * tablero, int i, int j)
{
	if((tablero->matriz)[j][i]==0)
	{
		int h;
		for(h=i; h-1>=0 && (tablero->matriz)[j][h-1]!='0'; h--)
			(tablero->matriz)[j][h] = (tablero->matriz)[j][h-1];
		(tablero->matriz)[j][h]='0';
		decalarFils(tablero, i, j);
	}
}

void nullCols(TipoTablero * tablero)
{
	int i=0, j=(tablero->dim).columnas-1, filas = (tablero->dim).filas, k;
	char * aux;
	while(i<j)
	{
		if((tablero->matriz)[j][filas-1]=='0')
			j--;
		else
		{
			if( (tablero->matriz)[i][filas-1]!='0')
				i++;
			else
			{
				aux = (tablero->matriz)[i];
				for(k=i; k<j; k++)
					(tablero->matriz)[k]=(tablero->matriz)[k+1];
				(tablero->matriz)[k] = aux;
			}
		}
	}
}

 int algunAdyacente(TipoTablero * tablero, int i, int j)
{
	char color = (tablero->matriz)[j][i];
	int filas = (tablero->dim).filas, columnas = (tablero->dim).columnas, h, k;
	for(k=j-1; h<=j+1; j++)
		for(h=i-1; h<=i+1; h++)
			if(h>=0 && h<(tablero->dim).filas && k>=0 && k<(tablero->dim).columnas && (MOD(h-i)+MOD(k-j))==1 )
				if((tablero->matriz)[k][h] == color)
					return 1;
	return 0;
}

 int analisisMatriz(TipoTablero * tablero)
{
	int filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	int i, j, aux;
	aux = ( (tablero->c_habilidades).c_martillazos != 0 ||
		(tablero->c_habilidades).c_hileras != 0 ||
		(tablero->c_habilidades).c_columnas != 0 );
	if(aux)
		return 1;
	for(j=0; j<columnas && (tablero->matriz)[j][filas-1]!='0'; j++)
		for(i=filas-1; i>=0 && (tablero->matriz)[j][i]!='0'; i--)
			if(algunAdyacente(tablero, i, j))
				return 1;
	return 0;
}
