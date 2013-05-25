#include "tilesBack.h"
#include "tilesFront.h"

int main(void)
{	TipoFlag  Flags = {OFF,OFF,OFF,OFF};
	TipoDatos dato;
		
	srand(time(NULL));	
	
	while(Flags[FIN_APLICACION]==OFF) 
	{
		Menu(&dato,Flags);

		while(Flags[FIN_JUEGO]==OFF)
		{	
			if(Flags[PROX_NIVEL]==ON)
			{  	
				Flags[PROX_NIVEL]=OFF;// falto El flag PROX_NIVEL ON si se carga una partida

				if(Crear_Nivel(&dato) == SIN_MEMORIA)
				{
					printerror(SIN_MEMORIA);
					return;
				}

			}
		
			imprimirEstado(&dato);
			imprimeTablero(&(dato.tablero));
			AccionesDeJuego(&dato,Flags);
		}
	}
	
	return 0;
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
			Flags[PROX_NIVEL]=ON;
			Flags[FIN_JUEGO]=OFF;
			(dato->tablero).c_habilidades.c_martillazos=0;
			(dato->tablero).c_habilidades.c_hileras=0;
			(dato->tablero).c_habilidades.c_columnas=0; 
			PedidoDimenciones(dato);  
			PedidoNivel(dato);
			
			break;
		case 3:  //LOAD
			 Flags[PROX_NIVEL]=OFF; //Setear flag de que se hizo load FIJAR DONDE DECLARARSE
			break;
	}
}

void PedidoNivel(TipoDatos * dato)
{
	TipoEstado nivel_ok = OFF;

	do
	{

	dato->nivel_max_usuario = getint("Ingrese hasta que nivel desea jugar: ");
	
	nivel_ok = NIVCHECK(dato->nivel_max_usuario,(dato->tablero).dim.filas,(dato->tablero).dim.columnas);		

	}while(nivel_ok == OFF);

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
			cant = sscanf(operacion+1,"uit%c",&aux);

			if(cant == EOF)
			{
				int comp_si;
				int comp_no;
		
				do{
			
					printf("Desea guardar la partida [SI\\NO]\n");
			
					inputString(respuesta);

					comp_si = strcmp(respuesta,"SI");
					int comp_no = strcmp(respuesta,"NO");
						
					if(comp_si==0)
					{
						do{	
							printf("Ingrese un nombre valido: \n");
							scanf("%30s%c",nombrefile,&aux);
						}while(!validFileName(nombrefile));
		
						//save(dato,nombrefile);
						Flags[FIN_APLICACION]=ON;
						Flags[FIN_JUEGO]=ON;
					}
					else if(comp_no==0)
					{
						Flags[FIN_APLICACION]=ON;
						Flags[FIN_JUEGO]=ON;
					}
					else
					{
						printf("Respuesta no valida\n");
					}

				}while(comp_si != 0 && comp_no != 0);
			}
			else
				printerror(COMANDO_INVALIDO);	
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
			resultadoFindelNivel(dato,Flags);
	
		}
		else if(!analisisMatriz(&(dato->tablero)))
		{
			Flags[FIN_JUEGO]=ON;
			printf("¡Perdiste al piste!\n");
		}
	}
	
}

void resultadoFindelNivel(TipoDatos * dato,TipoFlag Flags)
{
	Flags[PROX_NIVEL]=ON;
	printf("Felicitaciones Completo el Nivel %d\n",dato->nivel);
	printf("Puntaje Final del Nivel: %d\n",dato->puntaje);

	if(dato->nivel == dato->nivel_max_usuario)
	{
		printf("¡¡Ganaste el juego, FELICITACIONES!!\n");
		Flags[FIN_JUEGO]=ON;
	}
}

void inputString(char * string)
{

	int longitud;

	fgets(string,MAX_LONG,stdin);

	longitud = strlen(string);

	if(longitud != 0)
	{
		if(string[longitud-1]=='\n')
			string[longitud-1]=0;
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
