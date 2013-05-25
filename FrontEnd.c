#include "tilesBack.h"
#include "tilesFront.h"

void main(void)
{	TipoFlag  Flags = {OFF,OFF,OFF,OFF};
	TipoDatos dato;
	int rta;
	
	srand(time(NULL));	
	
	while(Flags[END_APPLICATION]==OFF) 
	{
		Menu(&dato,Flags);

		while(Flags[GAME_OVER]==OFF)
		{		
	
			if(Flags[NEXT_LEVEL]==ON)
			{  	
				Flags[NEXT_LEVEL]=OFF; // El flag NEXT_LEVEL solo se pone en ON si: se carga una partida  o se pasa de nivel			
				rta = Crear_Nivel(&dato);
			}
		
			imprimirEstado(&dato);
			imprimeTablero(&(dato.tablero));
			AccionesDeJuego(&dato,Flags);
		}
	}
}

void imprimirEstado(TipoDatos * dato)
{
	printf("PUNTAJE: %d\nHABILIDADES --> MARTILLAZOS: %d|COLUMNAS: %d|HILERAS: %d\n",dato->puntaje,dato->tablero.c_habilidades.c_martillazos,dato->tablero.c_habilidades.c_columnas,dato->tablero.c_habilidades.c_hileras);
}


void Menu (TipoDatos * dato,TipoFlag Flags)
{
	int c;

	printf("Bienvenido:\n\n1 - Juego Nuevo \n2 - Juego con Bitacora \n3 - Cargar Partida\n\n\n","Ingresa Filas\n","Ingresa Columnas\n");

	do
	{
		c=getint("Ingrese una opcion: ");
	}while(c<1 || c>4);

	switch(c)
	{
		case 2: Flags[BITACORA]=ON; 
		case 1:
			dato->nivel=0;
			Flags[NEXT_LEVEL]=ON;
			Flags[GAME_OVER]=OFF;
			(dato->tablero).c_habilidades.c_martillazos=0;
			(dato->tablero).c_habilidades.c_hileras=0;
			(dato->tablero).c_habilidades.c_columnas=0; 
			PedidoDimenciones(dato);  
			
			break;
		case 3:  //LOAD
			 Flags[NEXT_LEVEL]=OFF; //Setear flag de que se hizo load FIJAR DONDE DECLARARSE
			break;
	}
}

void PedidoDimenciones(TipoDatos * dato)
{
	TipoEstado dim_ok = OFF;

	do
	{
	
	(dato->tablero).dim.filas= getint("Ingrese Cantidad de Filas: ");
	(dato->tablero).dim.columnas= getint("Ingrese Cantidad de Columnas: ");
	dim_ok = DIMCHECK((dato->tablero).dim.filas,(dato->tablero).dim.columnas);

	}while(dim_ok == OFF);

}


void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags)
{	
	static TipoDatos aux_datos;
	int cant,cant_azulejos;
	TipoPosicion pos;
	
	char operacion[MAX_LONG];
	char * nombrefile=malloc(MAX_LONG*sizeof(*nombrefile));

	char * respuesta=malloc(MAX_LONG*sizeof(*respuesta));
	
	char accion,aux;
	
	//aux_datos = dato ;//Se realiza un save temporal de los datos por si el usuario pide la operacion UNDO	
	
	inputString(operacion);

	sscanf(operacion,"%c",&accion);

	switch(accion)
	{
		case 'e': 

			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&(pos.x),&(pos.y),&aux);
				
			if(cant == 2)
			{
				cant_azulejos = eliminar(&(dato->tablero),pos.x,pos.y);
			}
			else
			{
				printerror(COMANDO_INVALIDO);
				return;	
			}
			break;
		case 'm':
			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&pos.x,&pos.y,&aux);
						
			if(cant == 2)
				cant_azulejos = martillazo(&(dato->tablero),pos.x,pos.y);
			else
			{
				printerror(COMANDO_INVALIDO);
				return;	
			}
			break;
		case 'c':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.y,&aux);
				
			if(cant == 1)
				cant_azulejos = columna(&(dato->tablero),pos.y);
			else
			{
				printerror(COMANDO_INVALIDO);
				return;	
			}
			break;
		case 'h':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.x,&aux);
			if(cant == 1)
				cant_azulejos = hilera(&(dato->tablero),pos.x);
			else
			{
				printerror(COMANDO_INVALIDO);
				return;	
			}
			break;
		case 's':
			cant = sscanf(operacion+1,"ave%*[ \t]%30s%c",nombrefile,&aux);

			if(cant == 1 && validFileName(nombrefile))
			{
				//save(dato,nombrefile);
			}
			else
				printerror(COMANDO_INVALIDO);
					
			return;

		case 'u': // VER LOGICA DEL UNDO 
			
				//*dato = aux_dato;
						
			return;

		case 'q':
			printf("Desea guardar la partida [SI\\NO]\n");
			
				inputString(respuesta);				
	
				if(strcmp( respuesta,"SI" )==0)
				{
					do{	
						printf("Ingrese un nombre valido: \n");
						scanf("%30s%c",nombrefile,&aux);
					}while(!validFileName(nombrefile));
			
					//save(dato,nombrefile);
					Flags[END_APPLICATION]=ON;
					Flags[GAME_OVER]=ON;
				}
				else if(strcmp( respuesta,"NO" )==0)
				{
					Flags[END_APPLICATION]=ON;
					Flags[GAME_OVER]=ON;
				}
				else
				{
					printf("Respuesta no valida\n\n");
				}
			return;

		default:
			
			printerror(COMANDO_INVALIDO);
			return;
			
	}

	if(cant_azulejos < 0) // Si la cantidad de azulejos es negativa implica que hay un error
	{
		printerror(cant_azulejos);
	}
	else
	{		
		Proc_Matriz(dato,cant_azulejos);
		if(nivelTerminado(&(dato->tablero)))
		{
			Flags[NEXT_LEVEL]=ON;
			printf("Completo el Nivel %d\n",dato->nivel);
	
		}
		else if(!analisisMatriz(&(dato->tablero)))
		{
			Flags[GAME_OVER]=ON;
			printf("¡Perdiste al piste!\n");
		}
	}
	
}

void inputString(char * string)
{

	int longitud_op;

	fgets(string,MAX_LONG,stdin);
	longitud_op = strlen(string);
	if(longitud_op != 0)
	{

		if(string[longitud_op-1]=='\n')
			string[--longitud_op]=0;

	}

}

int validFileName(char * nombrefile)
{	int i;

	for(i=0;nombrefile[i]!=0;i++)
	{
		if(!VALIDCHAR(nombrefile[i]))
		return 0;
	}
	return 1;
}

void printerror(int ind)
{
	char * error[]={"Comando no valido","Sin habilidades Especiales","Sin Memoria","Posicion Nula","Hilera nula","Columna Nula","No hay adyacencia","Fuera de Rango"};

	printf("ERROR: %s\n",error[ind*(-1)-1]);

}

void imprimeTablero(TipoTablero * tablero)
{
	
	int i, j, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	for(i=-1; i<filas; i++)
	{
		printf(" ");
		for(j=-1; j<columnas; j++)
		{
			if(i==-1 && j>=0)
			{
				printf("%-2d ", j);
			}
			else if(j==-1 && i>=0)
			{
				printf("%2d  ", i);
			}
			else if(j>=0 && i>=0)
			{
				if((tablero->matriz)[j][i] != 0  && (tablero->matriz)[j][i]!='0')
				{
					printf("%c  ", (tablero->matriz)[j][i]);
				}
				else
				{
					printf("   ");
				}
			}
			else
			{
				printf("    ");
			}
		}
		putchar('\n');
	}
}
