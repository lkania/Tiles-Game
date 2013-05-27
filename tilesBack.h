#ifndef tilesBack_H
#define tilesBack_H

#define MOD(x) ( ((x)>=0)?(x):-(x) )

enum errores {FUERA_RANGO=-12,SIN_ADYACENCIA,COLUMNA_NULA,HILERA_NULA,POSICION_NULA,SIN_MEMORIA,NO_HAB,COMANDO_INVALIDO,FALLO_LECTURA,FALLO_ESCRITURA,OPERACION_INVALIDA, ARCHIVO_INEXISTENTE};

enum colores {NEGRO=0, ROJO, VERDE, AMARILLO, AZUL, VIOLETA, CELESTE, BLANCO};

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
	TipoDimension dim;
	TipoHabilidades c_habilidades;
}TipoTablero;

typedef struct
{
	TipoTablero tablero;
	int nivel_max_usuario;
	int puntaje;
	int nivel;
}TipoDatos;

int generarAuxiliar(TipoDatos * aux_dato,int filas,int columnas);
void igualacion(TipoDatos * aux_dato,TipoDatos * ori_dato);

int Crear_Nivel(TipoDatos * dato); // devuelve 0 si pudo crearse el nivel, SIN_MEMORIA en otro caso
void Proc_Matriz(TipoDatos * dato, int azulejos);
static int calcularPuntaje(const TipoDimension * dim, int azulejos);
static void bonus(TipoHabilidades * habilidades, const TipoDimension * dim, int puntaje);//incrementa habilidades segun bonus

// nivelTerminado debe llamarse antes de analisisMatriz!!!
int nivelTerminado(TipoTablero * tablero); // devuelve 1 si termino el nivel, 0 si no
int analisisMatriz(TipoTablero * tablero); //devuelve 0 si no puedo jugar mas, 1 si puedo seguir jugando
static int algunAdyacente(TipoTablero * tablero, int i, int j);//funcion auxiliar de analisisMatriz

static int generarTablero(TipoDatos * dato); //Genera el tablero de juego en cada nivel
static int coloresPresentes(TipoTablero * tablero, char * colores); // funcion auxiliar de generarTablero
static void liberarMatriz(TipoTablero * tablero);
int generarTableroNull(TipoTablero * tablero);

//Cada uno de las siguientes funciones devuelve cuantos azulejos se rompieron, si es que se pudo.
//o un numero negativo caracteristico que indica el error que hubo. NUNCA DEVUELVEN 0
int eliminar(TipoTablero * tablero, int i, int j);
int martillazo(TipoTablero * tablero, int i, int j);
int hilera(TipoTablero * tablero, int hilera);
int columna(TipoTablero * tablero, int columna);

static void elimAd(TipoTablero * tablero, int i, int j, char tipo, int * azulejos);//funcion auxiliar de funcion "eliminar"

//Las siguientes son funciones auxiliares de sus respectivos movimientos
static int validarEliminar(TipoTablero * tablero, int i, int j);
static int validarMartillazo(TipoTablero * tablero, int i, int j);
static int validarHilera(TipoTablero * tablero, int hilera);
static int validarColumna(TipoTablero * tablero, int columna);

static void gravedad(TipoTablero * tablero);//tras su invocacion "caen" las piezas hasta que no haya espacios libres
static void decalarFils(TipoTablero * tablero, int i, int j); //funcion auxiliar para gravedad
static void nullCols(TipoTablero * tablero);//decala hacia la izquierda las columnas nulas

void setColor(int color);
/*COLORES
	printf("%c[1;20mHello, world!\n", 27); // verde matrix
	printf("%c[1;21mHello, world!\n", 27); // verde matrix
	printf("%c[1;30mHello, world!\n", 27); // negro
	printf("%c[1;31mHello, world!\n", 27); // rojo
  	printf("%c[1;32mHello, world!\n", 27); // verde
  	printf("%c[1;33mHello, world!\n", 27); // amarillo
	printf("%c[1;34mHello, world!\n", 27); // azul
	printf("%c[1;35mHello, world!\n", 27); // violeta
	printf("%c[1;36mHello, world!\n", 27); // celeste
	printf("%c[1;37mHello, world!\n", 27); // blanco
	printf("%c[1;38mHello, world!\n", 27); // blanco
	printf("%c[1;39mHello, world!\n", 27); // verde oscuro
*/

#endif
