#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tilesBack.h";

void acciones(TipoDatos * dato);
{
	char * operacion

	fgets(


	if(dato->flags[NEXT_LEVEL]==ON)
	{
		nextlevel();
		// generarTablero(dato) va dentro de next level
	}
	else if(accion->operacion == SAVE || accion->operacion == LOAD ) 
	{
		Admin_Arch(dato);
	}
	else
	{
		ProcesamientoMatriz(dato,accion);
	}
}

// FUNCION next level que haga todo lo necesario al principio de nivel(subir nivel, calcular bonu,etc);

static void Admin_Arch
	// MANEJA SI EL usuario pone save o elige load, sino no entro

static void ProcesamientoMatriz(TipoDatos * dato,TipoAccion * accion)
{
	int cant_azulejos;
	
	

	if(accion->flag[BITACORA]==ON)
	{
		//log(accion,datos)
	}

	
	
	
		dato->puntaje = CalcularPuntaje(cant_azulejos);

		gravedad(dato);

		if(dato->cant_habilidades.cant_martillazos > 0 || dato->cant_habilidades.cant_martillazos >0 || dato->cant_habilidades.cant_martillazos > 0)
		{
			analisisMatriz(dato); //Modifica el FLAG GAME_OVER dependiendo de si se puede seguir jugando o no
						
		}

		GanoNivel(dato) // si la matriz es nula --> gano el nivel, modifcar el flag NEXT_LEVEL=ON
	}
	else
		return;
}


