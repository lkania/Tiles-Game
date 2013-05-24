#ifndef tilesBack_H
#define tilesBack_H
#define MOD(x) ( ((x)>=0)?(x):(-x) )

enum operaciones {UNDO=0,SAVE,ELIMINAR,HILERA,COLUMNA,MARTILLAZO};
typedef enum operaciones TipoOperacion;

enum errores {FUERA_RANGO=-6,SIN_ADYACENCIA,COLUMNA_NULA,HILERA_NULA,POSICION_NULA,SIN_MEMORIA,NO_HAB};

enum indices {BITACORA=0,NEXT_LEVEL,GAME_OVER}; 

enum estados {ON=0,OFF};
typedef enum estados TipoFlag;
typedef TipoFlag Flags[3]; //1er FLAG: BITACORA, 2do FLAG: NEXT LEVEL, 3er FLAG: GAME OVER

typedef struct
{
	int x,y;
}TipoPosicion;

typedef struct
{
	int filas,columnas;
}TipoDimension;

typedef struct
{
	int c_martillazos;
	int c_columnas;
	int c_hileras;
}TipoHabilidades;

typedef struct
{
	char ** matriz;
	TipoHabilidades c_habilidades;
	TipoDimension dim;
}TipoTablero;

typedef struct
{
	TipoTablero tablero;
	int puntaje;
	int nivel;
}TipoDatos;

void Crear_Nivel(TipoDatos * dato);
 
/*
void analisisMatriz(TipoDatos * dato); //Modifica el FLAG GAME_OVER dependiendo de si se puede seguir jugando o no

void generarTablero(TipoDatos * dato); //Genera el tablero de juego en cada nivel

int algunAdyacente(TipoDatos * dato, int i, int j);

//Cada uno de las siguientes funciones devuelve cuantos azulejos se rompieron
int eliminar(TipoDatos * dato,TipoAccion * accion);
int martillazo(TipoDatos * dato,TipoAccion * accion);
int hilera(TipoDatos * dato,TipoAccion * accion);
int columna(TipoDatos * dato,TipoAccion * accion);

static void elimAd(TipoDatos * dato, int i, int j, char tipo, int * azulejos);//funcion auxiliar de funcion "eliminar"

//Validaciones de sus respectivos movimientos

static void validarEliminar(TipoDatos * dato,TipoAccion * accion);
static void validarMartillazo(TipoDatos * dato,TipoAccion * accion);
static void validarHilera(TipoDatos * dato,TipoAccion * accion);
static void validarColumna(TipoDatos * dato,TipoAccion * accion);

static void gravedad(TipoDatos * dato);//tras su invocacion "caen" las piezas hasta que no haya espacios libres
static void decalarFils(TipoDatos * dato, int i, int j); //funcion auxiliar para gravedad

static void nullCols(TipoDatos dato);//decala hacia la izquierda las columnas nulas
static void liberarMatriz(TipoDatos * dato);
*/
#endif

//CONVENCION: Matriz tipo c/f [columna][fila] ¡QUE HAGO!!! donde lo pongo
