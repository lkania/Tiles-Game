#include "tilesBack.h"
#include "tilesFront.h"

/*static char *menu[]={"Bienvenido:\n\n1 - Juego Nuevo \n2 - Juego con Bitacora \n3 - Cargar Partida\n\n\n","Ingresa Filas\n","Ingresa Columnas\n"}; variables globales are for pussies*/

void main(void)
{	TipoFlag  Flags;
	TipoDatos dato;
	
	Flags[BITACORA]=OFF;
	Flags[NEXT_LEVEL]=OFF;
	Flags[GAME_OVER]=OFF;

	Menu (&dato,Flags);
	while(1) // while(1) es para faggots
	{
	if(Flags[NEXT_LEVEL]==ON){  // El flag NEXT_LEVEL solo se pone en ON si: se carga una partida  o se pasa de nivel
		Flags[NEXT_LEVEL]=OFF;
		Crear_Nivel(&dato);
	}
	BORRAR_PANT
	imprimeTablero(&(dato.tablero));
	AccionesDeJuego(&dato,Flags); 
	}
}

void imprimeMenu(int menu)
{
	switch(menu)
	{
		case 1:
			printf("Bienvenido:\n\n1 - Juego Nuevo\n2 - Juego con Bitacora\n3 - Cargar Partida\n\n\n");
			break;
		case 2:
			printf("Ingresa Filas\n");
			break;
		case 3:
			printf("Ingresa Columnas\n");
			break;
	}
}


void Menu (TipoDatos * dato,TipoFlag Flags){
	int c;
	
	BORRAR_PANT

	do{
		printf("%s",menu[0]);
		c=getint("");
	}while(c<1 && c>4);

	switch(c){
		case 2:  Flags[BITACORA]=ON; // Hay que ver si no se pone en dato
		case 1:	 dato->nivel=0;
			  Flags[NEXT_LEVEL]=ON;
			 (dato->tablero).c_habilidades.c_martillazos=0;
			 (dato->tablero).c_habilidades.c_hileras=0;
			 (dato->tablero).c_habilidades.c_columnas ++; 
			 BORRAR_PANT
			 PedidoDimenciones(dato);  
			 break;
		case 3:  //LOAD
			 Flags[NEXT_LEVEL]=OFF; //Setear flag de que se hizo load FIJAR DONDE DECLARARSE
			 break;
	}
}

void PedidoDimenciones(TipoDatos * dato){
	BORRAR_PANT
	//FALTA VALIDAR DIMENSIONES	
	printf("%s",menu[1]);
	(dato->tablero).dim.filas= getint("fila: ");
	printf("%s",menu[2]);
	(dato->tablero).dim.columnas= getint("columna: ");
	return;

}





void Crear_Nivel(TipoDatos * dato){ /// FUNCION DEL BACKEND HAY QUE PONERLA EN TILES BACK!!!!!!!!!!!!!!!!!!!1

	dato->nivel++;
	dato->puntaje=0;
	(dato->tablero).c_habilidades.c_martillazos ++;
	(dato->tablero).c_habilidades.c_hileras ++;
	(dato->tablero).c_habilidades.c_columnas ++;
	//Falta calculo del bonus
	generarTablero(dato);

}





void AccionesDeJuego(TipoDatos * dato,TipoFlag Flags)
{	
	static TipoDatos aux_datos;

	int cant,cant_azulejos;
	TipoPosicion pos;
	TipoEstado fin_programa=OFF; // PONER EN FLAGS

	char operacion[MAX_LONG]={0};
	char nombrefile[MAX_LONG];
	char respuesta[2];

	int longitud_op;
	char accion,aux;

	//Se realiza un save temporal de los datos por si el usuario pide la operacion UNDO
	//aux_datos = dato	

	fgets(operacion,MAX_LONG,stdin);
	longitud_op = strlen(operacion);
	if(longitud_op != 0)
	{
	
		if(operacion[longitud_op-1]=='\n')
			operacion[--longitud_op]=0;

	}

	sscanf(operacion,"%c",&accion);


	switch(accion)
	{
		case 'e': 

			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&pos.x,&pos.y,&aux);

				
			if(cant == 2 && cant != EOF){
				printf("e \n");
				printf("cant %d,x: %d,y:%d\n",cant,pos.x,pos.y);
				cant_azulejos = eliminar(&(dato->tablero),pos.x,pos.y);
				printf("Azulejos: %d \n",cant_azulejos);
			}else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;
		/*case 'm':
			cant = sscanf(operacion+1,"%*[ \t]%d,%d%c",&pos.x,&pos.y,&aux);
						
			if(cant == 2 && cant != EOF)
				//cant_azulejos = martillazo(&(dato->tablero),pos.x,pos.y);
			else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;
		case 'c':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.y,&aux);
				
			if(cant == 1 && cant != EOF)
				//cant_azulejos = columna(&(dato->tablero),pos.y);
			else
			{
				printf("ERROR: COMANDO NO VALIDO\n");
				return;	
			}
			break;
		case 'h':
			cant = sscanf(operacion+1,"%*[ \t]%d%c",&pos.x,&aux);
			if(cant == 1 && cant != EOF)
				//cant_azulejos = hilera(&(dato->tablero),pos.x);
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

		case 'u': // VER LOGICA DEL UNDO 
			if(strcmp( respuesta,"SI" )==0){
				//*dato = aux_dato;
			}
			
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
		}else{		
			Proc_Matriz(dato);
		}

		return;

}


void Proc_Matriz(TipoDatos * dato) // SE PASA A BACKEND
{

	gravedad(&(dato->tablero));
	nullCols(&(dato->tablero));
	return;


}


int validFileName(char * nombrefile) // SE PASA A BACKEND
{	int i;

	for(i=0;nombrefile[i]!=0;i++)
	{
		if(!VALIDNAME(nombrefile[i]))
			return 0;
	}
		return 1;
}

void printerror(int ind){
	printf("%s\n",error+(ind*(-1)));

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
