static void generarTablero(TipoDatos * dato)
{
	//LLAMADO A srand(time(NULL)) lo hacemos UNA sola vez, y desde el main
	int i, j, indice, nivel = dato->nivel, filas = (dato->dim).filas, columnas = (dato->dim).columnas;
	char ** tablero = malloc(columnas*sizeof(char*));
	(dato->error) = NO_ERROR;
	if(tablero == NULL)
	{
		(dato->error) = SIN_MEMORIA; //AGREGAR ESTE ERROR
		return;
	}
	for(j=0; j<columnas; j++)
	{
		tablero[j] = malloc(filas);
		if(tablero[j] == NULL)
		{
			(dato->error) = SIN_MEMORIA;
			j--;
			for(;j>=0; j--)
				free(tablero[j]);
			free(tablero);
			return;
		}
	}
	for(j=0; j<columnas; j++)
	{
		for(i=0; i<filas; i++)
		{
			indice = rand()%(nivel+1);
			tablero[j][i] = 'A' + indice;
		}
	}
	(dato->matriz) = tablero;
}

static void liberarMatriz(TipoDatos * dato)
{
	int j, columnas = (dato->dim).columnas;
	for(j=0; j<columnas; j++)
		free((dato->matriz)[j]);
	free(dato->matriz);
}

static void elimAd(TipoDatos * dato, int i, int j, char tipo, int * azulejos)
{
	if((dato->matriz)[j][i]==tipo)
	{
		int h, k;
		(dato->matriz)[j][i]='\0';
		(*azulejos)++;
		for(h=i-1; h<=i+1; h++)
			for(k=j-1; h<=j+1; j++)
				if(h>=0 && h<(dato->dim).filas && k>=0 && k<(dato->dim).columnas && (MOD(h-i)+MOD(k-j))==1 )
					elimAd(dato, h, k, tipo, azulejos);
	}
}

static int eliminar(TipoDatos * dato,TipoAccion * accion)
{
	int azulejos=0, i = (accion->coordenada).x, j = (accion->coordenada).y;
	char tipo = (dato->matriz)[j][i];
	elimAd(dato, i, j, tipo, &azulejos);
	return azulejos;
}

static int martillazo(TipoDatos * dato,TipoAccion * accion)
{
    int h, k, azulejos = 0, i = (accion->coordenada).x, j = (accion->coordenada).y;
    for(k=j-1; k<=j+1; k++)
	{
        for(h=i-1; h<=i+1; h++)
		{
            if(h>=0 && h<(dato->dim).filas && k>=0 && (dato->dim).columnas && (dato->matriz)[k][h]!=0)
			{
                (dato->matriz)[k][h] = '\0';
				azulejos++;
			}
		}
	}
	return azulejos;
}

static int hilera(TipoDatos * dato,TipoAccion * accion)
{
    int j, azulejos=0, hilera = (accion->coordenada).x;
    for(j=0; j<(dato->dim).columnas; j++)
	{
		if((dato->matriz)[j][hilera]!=0)
		{
			(dato->matriz)[j][hilera] = '\0';
			azulejos++;
		}
	}
	return azulejos;
}

static int columna(TipoDatos * dato,TipoAccion * accion)
{
    int i, azulejos = 0, columna = (accion->coordenada).y;
    for(i=0; i<(dato->dim).filas; i++)
	{
		if((dato->matriz)[columna][i]!=0)
		{
        	(dato->matriz)[columna][i] = '\0';
			azulejos++;
		}
	}
	return azulejos;
}

static void validarEliminar(TipoDatos * dato,TipoAccion * accion)
{
	TipoError error = NO_ERROR;
	int aux, filas = (dato->dim).filas, columnas = (dato->dim).columnas;
	int i = (accion->coordenada).x, j = (accion->coordenada).y;
	char tipo;
	if(i<0 || i>=filas || j<0 || j>=columnas)
		error = FUERA_RANGO;
	else if((dato->matriz)[j][i]=='0')
			error = POSICION_NULA;
	else
	{
		tipo = (dato->matriz)[j][i];
		aux = ((i-1>=0 && (dato->matriz)[j][i-1]==tipo)||
			(j-1>=0 && (dato->matriz)[j-1][i]==tipo)||
			(i+1<filas && (dato->matriz)[j][i+1]==tipo)||
			(j+1<columnas && (dato->matriz)[j+1][i]==tipo));
		if(!aux)
			error = SIN_ADYACENCIAS;
	}
	(dato->error) = error;
}

static void validarMartillazo(TipoDatos * dato,TipoAccion * accion)
{
	TipoError error = NO_ERROR;
	int filas = (dato->dim).filas, columnas = (dato->dim).columnas;
	int i = (accion->coordenada).x, j = (accion->coordenada).y;
	if(i<0 || i>=filas || j<0 || j>=columnas)
		error = FUERA_RANGO;
	else if((dato->matriz)[j][i]!='0')
		error = POSICION_NULA;
	(dato->error) = error;
}

static void validarHilera(TipoDatos * dato,TipoAccion * accion)
{
	TipoError error= HILERA_NULA;
	int j, flag = 0, filas = (dato->dim).filas, columnas = (dato->dim).columnas;
	int hilera = (accion->coordenada).x;
	if(hilera<0 || hilera >= filas)
		error = FUERA_RANGO;
	else
	{
		for(j=0; j<columnas && !flag; j++)
		{
			if((dato->matriz)[j][hilera]!='0')
			{
				flag = 1;
				error = NO_ERROR;
			}
		}
	}
	(dato->error) = error;
}

static void validarColumna(TipoDatos * dato,TipoAccion * accion)
{
	TipoError error= COLUMNA_NULA;
	int i, flag = 0, filas = (dato->dim).filas, columnas = (dato->dim).columnas;
	int columna = (accion->coordenada).y;
	if(columna < 0 || columna >= columnas)
		error = FUERA_RANGO;
	else
	{
		for(i=0; i<filas && !flag; i++)
		{
			if((dato->matriz)[columna][i]!='0')
			{
				flag = 1;
				error = NO_ERROR;
			}
		}
	}
	(dato->error) = error;
}

static void gravedad(TipoDatos * dato)
{
	int i, j, filas = (dato->dim).filas, columnas = (dato->dim).columnas;
	for(j=0; j<columnas; j++)
	{
		for(i=filas-1; i>=0 && (dato->matriz)[j][i]!='0'; i--)
		{
			if((dato->matriz)[j][i] == 0)
			{
				decalarFils(dato, i, j);
			}
		}
	}
}

static void decalarFils(TipoDatos * dato, int i, int j)
{
	if((dato->matriz)[j][i]==0)
	{
		int h;
		for(h=i; h-1>=0 && (dato->matriz)[j][h-1]!='0'; h--)
			(dato->matriz)[j][h] = (dato->matriz)[j][h-1];
		(dato->matriz)[j][h]='0';
		decalarFils(dato, i, j);
	}
}

static void nullCols(TipoDatos * dato)
{
	int i=0, j=(dato->dim).columnas-1, filas = (dato->dim).filas, k;
	char * aux;
	while(i<j)
	{
		if((dato->matriz)[j][filas-1]=='0')
			j--;
		else
		{
			if( (dato->matriz)[i][filas-1]!='0')
				i++;
			else
			{
				aux = (dato->matriz)[i];
				for(k=i; k<j; k++)
					(dato->matriz)[k]=(dato->matriz)[k+1];
				(dato->matriz)[k] = aux;
			}
		}
	}
}

static int algunAdyacente(TipoDatos * dato, int i, int j)
{
	char color = (dato->matriz)[j][i];
	return ( (i-1>=0 && (dato->matriz)[j][i-1]==color) ||
	(j-1>=0 && (dato->matriz)[j-1][i]==color) ||
	(i+1<filas && (dato->matriz)[j][i+1]==color) ||
	((dato->matriz)[j+1][i]==color) );
}

static void analisisMatriz(TipoDatos * dato)
{
	int filas = (dato->dim).filas, columnas = (datos->dim).columnas;
	int i, j, flag = 0;
	(dato->flags)[GAME_OVER] = ON;
	for(j=0; j<columnas && (dato->matriz)[j][filas-1]!='0' && !flag; j++)
	{
		for(i=filas-1; i>=0 && (dato->matriz)[j][i]!='0' && !flag; i--)
		{
			if(algunAdyacente(dato, i, j))
			{
				(dato->flags)[GAME_OVER] = OFF;
				flag = 1;
			}
		}
	}
}


