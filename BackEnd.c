#include <stdio.h>
#include <stdlib.h>
#include "tilesBack.h"

int Crear_Nivel(TipoDatos * dato)
{
	dato->nivel++;
	if((dato->nivel)>1)
	{
		bonus(&((dato->tablero).c_habilidades), &((dato->tablero).dim), dato->puntaje);
		liberarMatriz(&(dato->tablero));
	}
	dato->puntaje=0;
	(dato->tablero).c_habilidades.c_martillazos++;
	(dato->tablero).c_habilidades.c_hileras++;
	(dato->tablero).c_habilidades.c_columnas++;
	return generarTablero(dato);
}

void Proc_Matriz(TipoDatos * dato, int azulejos)
{
	gravedad(&(dato->tablero));
	nullCols(&(dato->tablero));
	dato->puntaje += calcularPuntaje(&((dato->tablero).dim), azulejos);
}


static int generarTablero(TipoDatos * dato)
{
        int i, j, indice, nivel = dato->nivel, filas = (dato->tablero).dim.filas, columnas = (dato->tablero).dim.columnas;
	char ** tablero = malloc(columnas*sizeof(char*));
	char * colores = malloc(nivel+2);
	colores[nivel+1]='\0';
	for(i=0; i<=nivel; i++)
		colores[i]='A'+i;
	if(tablero == NULL)
		return SIN_MEMORIA;
	for(j=0; j<columnas; j++)
	{
		tablero[j] = malloc(filas*sizeof(char));
		if(tablero[j] == NULL)
		{
			j--;
			for(;j>=0; j--)
				free(tablero[j]);
			free(tablero);
			return SIN_MEMORIA;
		}
	}
	putchar('\n');
	do
	{
		for(j=0; j<columnas; j++)
		{
			for(i=0; i<filas; i++)
			{
				indice = rand()%(nivel+1);
				tablero[j][i] = 'A' + indice;
			}
		}
		(dato->tablero).matriz = tablero;
	}while(!coloresPresentes(&(dato->tablero), colores));
        return 0;
}

static int coloresPresentes(TipoTablero * tablero, char * colores)
{
	int filas = (tablero->dim).filas, columnas = (tablero->dim).columnas, i, j, k, flag=0;
	for(k=0; colores[k] != '\0'; k++)
	{
		flag = 0;
		for(j=0; j<columnas && !flag; j++)
		{
			for(i=0; i<filas && !flag; i++)
			{
				if((tablero->matriz)[j][i]==colores[k])
					flag = 1;
			}
		}
		if(flag==0)
			return 0;
	}
	return 1;			
}

static void liberarMatriz(TipoTablero * tablero)
{
	int j, columnas = (tablero->dim).columnas;
	for(j=0; j<columnas; j++)
		free((tablero->matriz)[j]);
	free(tablero->matriz);
}

static void elimAd(TipoTablero * tablero, int i, int j, char tipo, int * azulejos)
{
	if((tablero->matriz)[j][i]==tipo)
	{
		int h, k;
		(tablero->matriz)[j][i]='\0';
		(*azulejos)++;
		for(k=j-1; k<=j+1; k++)
		{
			for(h=i-1; h<=i+1; h++)
			{
				if(h>=0 && h<(tablero->dim).filas && k>=0 && k<(tablero->dim).columnas && (MOD(h-i)+MOD(k-j))==1 )
				{
					elimAd(tablero, h, k, tipo, azulejos);
				}
			}
		}
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
        	    if(h>=0 && h<(tablero->dim).filas && k>=0 && k<(tablero->dim).columnas && (tablero->matriz)[k][h]!=0)
				{
        	        (tablero->matriz)[k][h] = '\0';
					azulejos++;
				}
			}
		}
		(tablero->c_habilidades).c_martillazos--;
	}
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
		(tablero->c_habilidades).c_hileras--;
	}
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
		(tablero->c_habilidades).c_columnas--;
	}
	return azulejos;
}

static int validarEliminar(TipoTablero * tablero, int i, int j)
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

static int validarMartillazo(TipoTablero * tablero, int i, int j)
{
	int filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	if(i<0 || i>=filas || j<0 || j>=columnas)
		return FUERA_RANGO;
	else if((tablero->matriz)[j][i]=='0')
		return POSICION_NULA;
	else if((tablero->c_habilidades).c_martillazos < 1)
		return NO_HAB;
	return 0;
}

static int validarHilera(TipoTablero * tablero, int hilera)
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

static int validarColumna(TipoTablero * tablero, int columna)
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

static void gravedad(TipoTablero * tablero)
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

static void decalarFils(TipoTablero * tablero, int i, int j)
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

static void nullCols(TipoTablero * tablero)
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

static int algunAdyacente(TipoTablero * tablero, int i, int j)
{
	char color = (tablero->matriz)[j][i];
	int filas = (tablero->dim).filas, columnas = (tablero->dim).columnas, h, k;
	for(k=j-1; k<=j+1; k++)
		for(h=i-1; h<=i+1; h++)
			if(h>=0 && h<(tablero->dim).filas && k>=0 && k<(tablero->dim).columnas && (MOD(h-i)+MOD(k-j))==1 )
				if((tablero->matriz)[k][h] == color)
					return 1;
	return 0;
}

int nivelTerminado(TipoTablero * tablero)
{
	return (tablero->matriz)[0][(tablero->dim).filas-1]=='0';
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

static int calcularPuntaje(const TipoDimension * dim, int azulejos)
{
	int totalAzulejos = (dim->filas)*(dim->columnas);
	if(azulejos == 1)
		return 1;
	else if(1 < totalAzulejos < 0.3*totalAzulejos)
		return (2*azulejos);
	else if(0.3*totalAzulejos <= azulejos < 0.6*totalAzulejos)
		return (3*azulejos);
	return (4*azulejos);
}

static void bonus(TipoHabilidades * habilidades, const TipoDimension * dim, int puntaje)
{
	int totalAzulejos = (dim->filas)*(dim->columnas);
	if(puntaje >= 3*totalAzulejos)
	{
		habilidades->c_martillazos++;
		habilidades->c_columnas++;
		habilidades->c_hileras++;
	}
	else if(puntaje >= 2*totalAzulejos)
	{
		habilidades->c_columnas++;
		habilidades->c_hileras++;
	}
	else
		habilidades->c_hileras++;
}
