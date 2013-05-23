#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tilesBack.h"

#define	MAX_LONG	30
#define VALIDNAME(c)	(isalnum(c) || c =='_' || c=='-')
#define	FREE_BUFFER	while(getchar()!='\n')

// Poner estas definiciones en un .h
// Vector de errores Poner STRINGS DE ERRRORES  char *error=

void AccionesDeJuego(void);//TipoDatos * dato
void printerror(int ind);
int validFileName(char * nombrefile);


void main(void)
{	
	
	AccionesDeJuego();
	

}

void AccionesDeJuego(void)
{	
	//static TipoDatos aux_datos;
	
	int cant,cant_azulejos;
	TipoPosicion pos;
	TipoFlag fin_programa=OFF;
	
	char operacion[MAX_LONG];
	char nombrefile[MAX_LONG];
	char respuesta[2];
	
	int longitud_op;
	char accion,aux;
	
	//Se realiza un save temporal de los datos por si el usuario pide la operacion UNDO
	//aux_datos = dato	

	fgets(operacion,MAX_LONG,stdin);

	if(operacion != NULL)
	{
		longitud_op = strlen(operacion);

		if(operacion[longitud_op-1]=='\n')
			operacion[--longitud_op]=0;

	}

	sscanf(operacion,"%c",&accion);

	
	switch(accion)
	{
		case 'e': 

			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&pos.x,&pos.y,&aux);
					
			printf("cant %d,x: %d,y:%d\n",cant,pos.x,pos.y);	
			if(cant == 2 && cant != EOF)
				printf("e");
				//cant_azulejos = eliminar(dato->tablero,pos.x,pos.y);
			else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;
		/*case 'm':
			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&pos.x,&pos.y,&aux);
						
			if(cant == 2 && cant != EOF)
				//cant_azulejos = martillazo(dato->tablero,pos.x,pos.y);
			else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;
		case 'c':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.y,&aux);
				
			if(cant == 1 && cant != EOF)
				//cant_azulejos = columna(dato->tablero,pos.y);
			else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;
		case 'h':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.x,&aux);
			if(cant == 1 && cant != EOF)
				//cant_azulejos = hilera(dato->tablero,pos.x);
			else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;*/
		case 's':
			cant = sscanf(operacion+1,"ave%*[ \t]%30s%c",nombrefile,&aux);
				
			if(cant == 1 && cant != EOF && validFileName(nombrefile))
			{
				printf("llego a save\n");								
				//save(dato,nombrefile);
			}
			else
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			break;

		case 'u':
			//dato = aux_dato;
			break;

		case 'q':
			while(fin_programa==OFF)
			{
				printf("Desea guardar la partida [SI\\NO]\n");
				scanf("%s",respuesta);
				
				if(strcmp( respuesta,"SI" )==0)
				{
					do{	
						printf("Ingrese un nombre valido: \n");
						scanf("%30s%c",nombrefile,&aux);
					}while(!validFileName(nombrefile));
						//save(dato,nombrefile);
						fin_programa=ON;
				}else{
					if(strcmp( respuesta,"NO" )==0)
						fin_programa=ON;
					else
						printf("Respuesta no valida\n\n");
				}


				
			}
			exit(0);
			break;


		/*default:*/
	}

		if(cant_azulejos < 0) // Si la cantidad de azulejos es negativa implica que hay un error
		{
			printerror(cant_azulejos);
		}

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

void printerror(int ind){
	printf("%s\n",error[ind]);

}

