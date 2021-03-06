#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tilesBack.h"
#include "tilesFront.h"
#include "getnum.h"

int main(void)
{
	TipoFlag  Flags = {OFF,OFF,OFF,OFF,OFF,OFF};
	TipoDatos dato;
    	TipoBitacora bitacora={NULL,"bitacora.txt"};
    	TipoDatos aux_dato;
	cambiarColor(BLANCO);
	aux_dato.tablero.matriz=NULL;
   	dato.tablero.matriz=NULL;
	srand(time(NULL));	
	
	Presentacion();

	while(Flags[FIN_APLICACION]==OFF) 
	{
		Menu(&dato,Flags,&bitacora);
	
		if(Flags[BITACORA]==ON)
		{
			if (Flags[PROX_NIVEL]==ON) // PROX_LEVEL ON implica que no se hizo ningun load
			{
				if((bitacora.archivo_bitacora=fopen(bitacora.nombre_bitacora,"w+t"))== NULL)
				{
					printerror(SIN_MEMORIA);
					Flags[BITACORA]=OFF;
				}

			}
			else
			{
				if((bitacora.archivo_bitacora=fopen(bitacora.nombre_bitacora,"r+"))== NULL)
				{
					printerror(SIN_MEMORIA);
					Flags[BITACORA]=OFF;
				}
				else if(fseek(bitacora.archivo_bitacora,0,SEEK_END)!=0)
				{
	                        	printerror(ARCHIVO_INEXISTENTE);
					Flags[BITACORA]=OFF;
				}

			}
		
			if(Flags[BITACORA]==OFF)
					printf("Bitacora Desactivada\n");
			
	    	}
		
		if(aux_dato.tablero.matriz!=NULL)
			free(aux_dato.tablero.matriz);
		if(dato.tablero.matriz!=NULL && Flags[PROX_NIVEL]!=OFF)
			free(dato.tablero.matriz);
	
		aux_dato.tablero.dim=dato.tablero.dim;
	
		if( Flags[FIN_JUEGO]==OFF &&  generarTableroNull(&aux_dato.tablero)==SIN_MEMORIA  )
		{
			printerror(SIN_MEMORIA);
			printf("No es posible utilizar UNDO\n");
			return 1;
		}

		while(Flags[FIN_JUEGO]==OFF)
		{
			if(Flags[PROX_NIVEL]==ON)
			{  	
				Flags[PROX_NIVEL]=OFF;

				if(Crear_Nivel(&dato) == SIN_MEMORIA)
				{
					printerror(SIN_MEMORIA);
					return 1;
				}

				Flags[UNDO]=ON;

				if(Flags[BITACORA]==ON)
				{  
					if(GuardarMATBitacora(&(dato.tablero),bitacora.archivo_bitacora)==FALLO_ESCRITURA)
					{
						printerror(FALLO_ESCRITURA);
						printf("Bitacora Desactivada\n");
						Flags[BITACORA]=OFF;
					}
		
				}

			}

			imprimirEstado(&dato);
			imprimeTablero(&(dato.tablero));
				
			AccionesDeJuego(&dato,Flags,bitacora,&aux_dato);
		}
	}

	if(Flags[BITACORA]==ON)
		fclose(bitacora.archivo_bitacora);

	return 0;
}

void imprimirEstado(TipoDatos * dato)
{
	printf("PUNTAJE: %d\nHABILIDADES --> MARTILLAZOS: %d|COLUMNAS: %d|HILERAS: %d\n",dato->puntaje,dato->tablero.c_habilidades.c_martillazos,dato->tablero.c_habilidades.c_columnas,dato->tablero.c_habilidades.c_hileras);
}

void Menu (TipoDatos * dato,TipoFlag Flags,TipoBitacora * bitacora )
{
	char * nombrefile=malloc(MAX_LONG_FILE*sizeof(*nombrefile));
	int c;

	printf("Bienvenido:\n1 - Juego Nuevo \n2 - Juego con Bitacora \n3 - Cargar Partida\n4 - Instrucciones\n5 - Salir del Juego\n");

	do
	{
		c=getint("Ingrese una opcion: ");
	}while(c<1 || c>5);

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
		case 3:
			if(nombrefile != NULL)
			{
				int aux;
				PedirNombreValido(nombrefile);			

				if((aux=load(dato,&(Flags[BITACORA]),nombrefile)) < 0)
				{ 
					printerror(aux);
					Flags[FIN_JUEGO]=ON;
				}
				else
				{
					printf("Cargado\n");	
					if (Flags[BITACORA]==ON)
					{	
						sprintf(bitacora->nombre_bitacora,"%s.txt",nombrefile);
		        			printf("%s\n\n",bitacora->nombre_bitacora);
					}
		      			Flags[UNDO]=ON;
					Flags[PROX_NIVEL]=OFF;
		        		Flags[FIN_JUEGO]=OFF;
				}
                	}
			else
				printerror(SIN_MEMORIA); 
				//Solo da error si el usuario elige cargar un archivo y no hay memoria suficiente para alamacenar el nombre ingresado por el usuario
			break;
		case 4: 
			instrucciones();
			Flags[FIN_JUEGO]=ON;
			break;
		
		case 5:
		    Flags[FIN_APLICACION]=ON;
		    Flags[FIN_JUEGO]=ON;
		    break;
		
	}
	
	free(nombrefile);
}

void instrucciones(void)
{
	putchar('\n');
	printf("El objetivo es eliminar todas las valdosas del tablero\nLos movimientos posibles son:\n\
	e FILA,COLUMNA\t- ELMINAR CASILLERO Y ADYACENTES DEL MISMO COLOR\n\
	h FILA\t\t- ELIMNAR HILERA\n\
	c COLUMNA\t- ELIMNAR COLUMNA\n\
	m FILA,COLUMNA\t- ELMINAR CASILLERO Y SUS 8 ADYACENTES\n");
	printf("El tablero puede tener como dimensiones\n\tMINIMO: %d X %d\n\tMAXIMO: %d X %d\n",MIN_FIL,MIN_COL,MAX_FIL,MAX_COL);
	printf("Presione 'Q' pasa volver al menu\n");
	while(getchar() != 'Q');
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


void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags,TipoBitacora bitacora,TipoDatos * aux_dato)
{	
	int cant,cant_azulejos=0;
	TipoPosicion pos;
	char operacion[MAX_LONG];
	char * nombrefile=malloc(MAX_LONG_FILE*sizeof(*nombrefile));
	char * respuesta=malloc(MAX_LONG*sizeof(*respuesta));
	char accion,aux,aux2;
	
	inputString(operacion);

	sscanf(operacion,"%c",&accion);

	switch(accion)
	{
		case 'e': 

			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&(pos.x),&(pos.y),&aux);
				
			if(cant == 2 && ((cant_azulejos=validarEliminar(&(dato->tablero),pos.x,pos.y)) == 0))
			{
				igualacion(aux_dato,dato);
				cant_azulejos = eliminar(&(dato->tablero),pos.x,pos.y);
			}
			else
				cant_azulejos=(cant_azulejos!=0) ? cant_azulejos:COMANDO_INVALIDO;
			break;
		case 'm':
			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&pos.x,&pos.y,&aux);
						
			if(cant == 2 && ((cant_azulejos=validarMartillazo(&(dato->tablero),pos.x,pos.y)) == 0))
			{
				igualacion(aux_dato,dato);
				cant_azulejos = martillazo(&(dato->tablero),pos.x,pos.y);
			}
			else
				cant_azulejos=(cant_azulejos!=0) ? cant_azulejos:COMANDO_INVALIDO;
			break;
		case 'c':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.y,&aux);
				
			if(cant == 1 && ((cant_azulejos=validarColumna(&(dato->tablero),pos.y)) == 0))
			{
				igualacion(aux_dato,dato);
				cant_azulejos = columna(&(dato->tablero),pos.y);
			}
			else
				cant_azulejos=(cant_azulejos!=0) ? cant_azulejos:COMANDO_INVALIDO;
			break;
		case 'h':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.x,&aux);
			if(cant == 1 && ((cant_azulejos=validarHilera(&(dato->tablero),pos.x))==0))
			{
				igualacion(aux_dato,dato);
				cant_azulejos = hilera(&(dato->tablero),pos.x);
			}
			else
				cant_azulejos=(cant_azulejos!=0) ? cant_azulejos:COMANDO_INVALIDO;
			break;
		case 's':
			if(nombrefile != NULL)
			{
				cant = sscanf(operacion+1,"ave%*[ \t]%30s%c",nombrefile,&aux);

				if(cant == 1 && validFileName(nombrefile))
				{
					if(cant_azulejos=save(dato,Flags[BITACORA],nombrefile) >=0 )
					{
						printf("Salvado\n");
						if(Flags[BITACORA]==ON)
						{
							Flags[BITACORA]=GuardarAccionBitacora(bitacora.archivo_bitacora,operacion,Flags[PROX_NIVEL],dato->puntaje,cant_azulejos);
							Flags[SAVE]=ON;
						}
                        			if(Flags[BITACORA]==ON && compBit_File(bitacora.nombre_bitacora,nombrefile)!=0)
						{
                					cant_azulejos=SaveBitacora(nombrefile,bitacora.archivo_bitacora);
							if(cant_azulejos<0)
							{
                    						Flags[BITACORA]== OFF;
								printf("Bitacora Desactivada\n");
							}
						}	
					}
                    	
				}
				else
					cant_azulejos=COMANDO_INVALIDO;
			}
			else
				cant_azulejos=SIN_MEMORIA;
			break;

		case 'u':
			cant = strcmp(operacion+1,"ndo");
			
			if(cant == 0)
			{
				if(Flags[UNDO]==OFF)
				{
					Flags[UNDO]=ON;
					igualacion(dato,aux_dato);			
				}
				else
					cant_azulejos=OPERACION_INVALIDA;
			}
			else
					cant_azulejos=COMANDO_INVALIDO;
			break;
			
		case 'q':
			cant = strcmp(operacion+1,"uit");
			
			if (respuesta != NULL)
			{
				if(cant == 0)
				{
					int comp_si;
					int comp_no;
		
					do{
			
						printf("Desea guardar la partida [SI\\NO]\n");
			
						inputString(respuesta);

						comp_si = strcmp(respuesta,"SI");
						comp_no = strcmp(respuesta,"NO");
						
						if(comp_si==0)
						{
							PedirNombreValido(nombrefile);		
						
							if(save(dato,Flags[BITACORA],nombrefile) != 1)
								printerror(FALLO_ESCRITURA);
							else
							{
								printf("Salvado\n");                               
								if(Flags[BITACORA]==ON && compBit_File(bitacora.nombre_bitacora,nombrefile)!=0)
								{
									cant_azulejos=SaveBitacora(nombrefile,bitacora.archivo_bitacora);
								}
                            				}
						}
						else if(comp_si != 0 && comp_no != 0)
						{
							printf("Respuesta no valida\n");
						}

					}while(comp_si != 0 && comp_no != 0);
					Flags[FIN_APLICACION]=ON;
					Flags[FIN_JUEGO]=ON;

					if(cant_azulejos < 0)
						printerror(cant_azulejos);
	
					return;
				}
				else
					cant_azulejos=COMANDO_INVALIDO;
			}
			else
				cant_azulejos=SIN_MEMORIA;
					
			break;

		default:			
			cant_azulejos=COMANDO_INVALIDO;
			break;
			
	}

	if(cant_azulejos < 0) // Si la cantidad de azulejos es negativa implica que hay un error
	{
		printerror(cant_azulejos);
	}
	else if(cant_azulejos != 0)
	{	
		Flags[UNDO]=OFF;		
		Proc_Matriz(dato,cant_azulejos);
		if(nivelTerminado(&(dato->tablero)))
		{
			resultadoFindelNivel(dato,Flags);
	
		}
		else if(!analisisMatriz(&(dato->tablero)))
		{
			Flags[FIN_JUEGO]=ON;
			printf("No te quedan movimientos posibles\n");
			imprimeTablero(&(dato->tablero));
			printf("¡Perdiste al piste!\n");
		}
		
	}

	if(Flags[BITACORA]==ON && Flags[SAVE]==OFF)
	{	
		Flags[BITACORA]=GuardarAccionBitacora(bitacora.archivo_bitacora,operacion,Flags[PROX_NIVEL],dato->puntaje,cant_azulejos);
		
	}
	else
		Flags[SAVE]=OFF;
}

void PedirNombreValido(char * nombrefile)
{
	int cant;
	char aux;

	do{
		printf("Ingrese un nombre valido: \n");
		cant = scanf("%25s%c",nombrefile,&aux); // 25 = MAX_LONG_FILE
	}while(!validFileName(nombrefile) && cant!=1);
}

int validFileName(char * nombrefile)
{
	int i;

	for(i=0;nombrefile[i]!=0;i++)
		if(!VALIDCHAR(nombrefile[i]))
			return 0;
	return 1;
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

void printerror(int ind)
{
	char * error[]={"Sin habilidad Especial","Sin Memoria","Posicion Nula","Hilera nula","Columna Nula","No hay adyacencia","Fuera de Rango","Comando no valido","Fallo la lectura del archivo","Fallo la escritura del archivo","Operacion invalida","Archivo inexistente"};

	printf("ERROR: %s\n",error[ind*(-1)-1]);

	/*Cada error tiene un valor negativo, que multiplicandolo por (-1) se consigue el indice positivo correspondiente en el vector de errores*/

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
					imprimirColor((tablero->matriz)[j][i]);
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

int save(TipoDatos * dato, TipoEstado flagBitacora, char * nombre)
{
	FILE * archivo;
	int informacion[9], i, j, respuesta = 1;
	informacion[0] = (dato->tablero).dim.filas;
	informacion[1] = (dato->tablero).dim.columnas;
	informacion[2] = dato->nivel_max_usuario;
	informacion[3] = flagBitacora;
	informacion[4] = dato->nivel;
	informacion[5] = dato->puntaje;
	informacion[6] = (dato->tablero).c_habilidades.c_hileras;
	informacion[7] = (dato->tablero).c_habilidades.c_columnas;
	informacion[8] = (dato->tablero).c_habilidades.c_martillazos;
	archivo = fopen(nombre, "w");
	respuesta = fwrite(informacion, sizeof(int), 9, archivo) == 9;
	if(respuesta)
		for(i=0; i<informacion[0] && respuesta; i++)
			for(j=0; j<informacion[1] && respuesta; j++)
				if(fwrite(&((dato->tablero).matriz[j][i]), sizeof(char), 1, archivo) == 0)
					respuesta = 0;
	fclose(archivo);
	return (respuesta==0) ? FALLO_ESCRITURA:1;
}

int load(TipoDatos * dato, TipoEstado * flagBitacora, char * nombre)
{
	FILE * archivo;
	int informacion[9], aux, i, j, respuesta = 1;
	archivo = fopen(nombre, "r+");
	if(archivo == NULL)
		return ARCHIVO_INEXISTENTE;
	for(i=0; i<9 && respuesta; i++)
		respuesta = fread((informacion+i), sizeof(int), 1, archivo);
	(dato->tablero).dim.filas = informacion[0];
	(dato->tablero).dim.columnas = informacion[1];
	if(respuesta && (aux = generarTableroNull( &(dato->tablero))) )
		for(i=0; i<informacion[0]; i++)
			for(j=0; j<informacion[1]; j++)
				if(fread( &((dato->tablero).matriz[j][i]), sizeof(char), 1, archivo) == 0)
					respuesta = 0;
	respuesta = aux;
	if(respuesta)
	{
		(dato->tablero).dim.filas = informacion[0];
		(dato->tablero).dim.columnas = informacion[1];
		dato->nivel_max_usuario = informacion[2];
		*flagBitacora = informacion[3];
		dato->nivel = informacion[4];
		dato->puntaje = informacion[5];
		(dato->tablero).c_habilidades.c_hileras = informacion[6];
		(dato->tablero).c_habilidades.c_columnas = informacion[7];
		(dato->tablero).c_habilidades.c_martillazos = informacion[8];
	}
	fclose(archivo);
	if(respuesta==0)
		return FALLO_LECTURA;
	return respuesta;
}

TipoEstado GuardarAccionBitacora(FILE * archivo_bitacora,char * operacion, TipoEstado prox_nivel, int puntaje,int cant_azulejos)
{
	static int contador=1;
	char s[MAX_LONG];

	sprintf(s,"%d: %s; %d\n",contador,operacion,(cant_azulejos < 0) ? 0:puntaje);
	
	if(fputs(s,archivo_bitacora) == EOF)
	{
		printerror(FALLO_ESCRITURA);
		printf("Bitacora Desactivada\n");
		return OFF; 
	}

	contador++;

	if(prox_nivel==ON)
		contador=1;

	return ON;
}

int GuardarMATBitacora(TipoTablero * tablero,FILE * archivo_bitacora)
{
	int i, j, filas = (tablero->dim).filas, columnas = (tablero->dim).columnas;
	    
	for(i=0; i<filas; i++)
	{
		for(j=0; j<columnas; j++)
		{
		    	if(fputc((tablero->matriz)[j][i],archivo_bitacora) == EOF)
			{
				return FALLO_ESCRITURA; 
			}
			
		}
	
		if(fputc('\n',archivo_bitacora) == EOF)
			return FALLO_ESCRITURA;
	}
	
	return 0;
}

int SaveBitacora(char * nombrefile,FILE * arch_origen)
{
	char s[MAX_LONG_FILE+3];
	FILE *dest;
	char  str[MAX_LONG];
    	int error=0;
		
        if(fseek(arch_origen,0,SEEK_SET)!=0)
                error=ARCHIVO_INEXISTENTE;
	else
	{
		sprintf(s,"%s.txt",nombrefile);
		if((dest = fopen(s, "wt"))==NULL)        /* abro destino */
		{
			error=FALLO_ESCRITURA;
                }
		else
		{
			while(!feof(arch_origen) && error>=0)
			{
                        	fgets(str,MAX_LONG,arch_origen);
                        	
				if(ferror(arch_origen))
                        		error=FALLO_LECTURA;
				else
				{
					if(!feof(arch_origen))
						fputs(str, dest);
					if(ferror(dest))
		                    	     	error=FALLO_ESCRITURA;
				}
			}
			
			if(fclose(dest)==EOF)
			{
				error=FALLO_ESCRITURA;
			}
		}
	}

	if (error<0)
		return error;
	else
		return 0;
}
 
void imprimirColor(char caracter)
{
	int num = 31+(caracter-'A')%8;
	printf("%c[1;%dm%c  ", 27, num, caracter);
	cambiarColor(BLANCO);
}

int compBit_File(char * bit ,char *file)
{
	int i;
	for (i=0;file[i]!=0 && bit[i] != 0;i++)
	{
	        if (bit[i]!= file [i])
         		return 1;
   	}
		return (bit[i] != 0 && strcmp(bit+i,".txt")==0 )? 0:1;
}

void Presentacion (void)
{
    int i,num;
    char present []="\n\
  TTTTTT III L    EEEE  SSS    GGG   AA  M   M EEEE\n\
    TT    I  L    E    S      G     A  A MM MM E\n\
    TT    I  L    EEE   SSS   G  GG AAAA M M M EEE\n\
    TT    I  L    E        S  G   G A  A M   M E\n\
    TT   III LLLL EEEE SSSS    GGG  A  A M   M EEEE\n\
    \n\
    \n";
    
    
    for (i=0; present[i]!=0; i++) {
        if(isalpha(present[i])){
            num = 31+(present[i]-'A')%8;
            printf("%c[1;%dm%c", 27, num, present[i]);
            cambiarColor(BLANCO);
        }else putchar(present[i]);
    }
    
    printf("Un juego crado por:\n\
	Gutierrez, Ignacio\n\
        Kania, Lucas\n\
        Tylson, Emilio\n\
        \n\
        \n\
        TOQUE CUALQUIER TECLA\n");
    
    
    while((getchar())!='\n');
}

void cambiarColor(int color)
{
	if(color>=NEGRO && color<=BLANCO)
		printf("%c[1;%dm", 27, (color+30));
}
