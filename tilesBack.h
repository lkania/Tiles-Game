#ifndef tilesBack_H
#define tilesBack_H

#define MOD(x) ( ((x)>=0)?(x):-(x) )
#define SWAP(a, b, aux) aux=a;a=b;b=aux

enum errores {FUERA_RANGO=-7,SIN_ADYACENCIA,COLUMNA_NULA,HILERA_NULA,POSICION_NULA,SIN_MEMORIA,NO_HAB};

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

void igualacion(TipoDatos * aux_dato,TipoDatos * ori_dato); // copia la informacion de ori_dato en aux_dato

int Crear_Nivel(TipoDatos * dato); // devuelve 0 si pudo crearse el nivel, SIN_MEMORIA en otro caso
void Proc_Matriz(TipoDatos * dato, int azulejos); // Llama a gravedad, nullCols y actualiza el puntaje.
static int calcularPuntaje(const TipoDimension * dim, int azulejos);
static void bonus(TipoHabilidades * habilidades, const TipoDimension * dim, int puntaje);// incrementa habilidades segun bonus

/* Notese que nivelTerminado se llama antes que analisisMatriz.*/
int nivelTerminado(TipoTablero * tablero); // devuelve 1 si el jugador completo el nivel, 0 si no
int analisisMatriz(TipoTablero * tablero); //devuelve 0 si no puedo jugar mas, 1 si puedo seguir jugando

/* algunAdyacente es una funcion auxiliar de analisisMatriz. Devuelve 1 si el azulejo del elemento de la fila 'i', columna 'j' tiene
** almenos 1 adyacente del mismo color. Devuelve 0 en caso contrario
*/
static int algunAdyacente(TipoTablero * tablero, int i, int j);

/* Genera el tablero de juego en cada nivel. CONVENCION IMPORTANTE: La funcion generarTablero esta hecha de forma tal que
** para acceder a un elemento primero se indique columna y luego fila.
*/
static int generarTablero(TipoDatos * dato);

/* coloresPresentes es una funcion auxiliar de generarTablero. Devuelve 0 si alguno de los colores correspondientes al nivel
** para el cual generarTablero esta creando el tablero no se encuentra presente en el mismo. Devuelve 1 en caso contrario.
*/
//static int coloresPresentes(TipoTablero * tablero, char * colores);
static void liberarMatriz(TipoTablero * tablero); // Libera la memoria utilizada para la matriz
int generarTableroNull(TipoTablero * tablero); //Reserva espacio para un tablero sin asignar elementos en sus posiciones.

/* Cada uno de las siguientes funciones devuelve cuantos azulejos se rompieron, si es que se pudo.
 * o un numero negativo caracteristico que indica el error que hubo. NUNCA DEVUELVEN 0
 * Los azulejos destruidos son convertidos en 0.
 */
int eliminar(TipoTablero * tablero, int i, int j);
int martillazo(TipoTablero * tablero, int i, int j);
int hilera(TipoTablero * tablero, int hilera);
int columna(TipoTablero * tablero, int columna);

/* elimAd es una funcion recursiva auxiliar de la funcion "eliminar". Lo que hace es ir convirtiendo en ceros los elementos
 * adyacentes al elemento de la matriz elegido. Incluyendo al elemento elegido. Notese que antes de llamar a elimAd se
 * llama a validarEliminar, que se encarga de verificar que el elemento elegido esta adentro de la matriz, representa un color
 * y tiene almenos un elemento adyacente del mismo color.
 */
static void elimAd(TipoTablero * tablero, int i, int j, char tipo, int * azulejos);

/* Las siguientes son funciones auxiliares de sus respectivos movimientos.*/
int validarEliminar(TipoTablero * tablero, int i, int j);
int validarMartillazo(TipoTablero * tablero, int i, int j);
int validarHilera(TipoTablero * tablero, int hilera);
int validarColumna(TipoTablero * tablero, int columna);

static void gravedad(TipoTablero * tablero);//tras su invocacion "caen" las piezas hasta que no haya espacios libres

/* decalarFils es una funcion recursiva auxiliar para gravedad. Lo que hace es operar sobre la columna 'j' a partir de la fila 'i' si
 * es que dicho elemento es igual a 0. Opera decalando los elementos de las filas desde arriba hacia abajo, hasta toparse con
 * un ascii del cero, o hasta llegar a la fila 0.
 */
static void decalarFils(TipoTablero * tablero, int i, int j);
static void nullCols(TipoTablero * tablero);//decala hacia la izquierda las columnas nulas

/* Cambia el color del texto de la consola.*/
void cambiarColor(int color);
/*El metodo utilizado para cambiar el color es el uso de un printf
 *	printf("%c[1;30m", 27); // negro
 *	printf("%c[1;31m", 27); // rojo
 *	printf("%c[1;32m", 27); // verde
 *	printf("%c[1;33m", 27); // amarillo
 *	printf("%c[1;34m", 27); // azul
 *	printf("%c[1;35m", 27); // violeta
 *	printf("%c[1;36m", 27); // celeste
 *	printf("%c[1;37m", 27); // blanco
*/

#endif
