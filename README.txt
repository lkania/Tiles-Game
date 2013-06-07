------------------------------------
Tiles-Game
------------------------------------

	Un pequeño juego donde el objetivo es romper todos los azulejos de la matriz.

	Desarrollado puramanete en C ANSI (con expeción de los colores que solo pueden ser utilizados bajo LINUX, pero son opcionales).

	Desarolladores:
	 - Ignacio Gutierrez
	 - Lucas Kania
	 - Emilio Tylson
	 
	TP-PI-2013-1C-ITBA
	
	Para ver la documentación WEB ejecutar el archivo index.html
	Para utilizar los saves almacenados en 'Ejemplos-de-SAVES' copiar los saves a la carpeta donde se encuentra el ejecutable.

------------------------------------
Autorización a utilizar colores
------------------------------------

	Hola,
	con respecto al color en el printf, y para ser coherentes con lo que
	dijeron en el Taller y Laboratorio, sí se pueden usar siempre y cuando
	funcionen en el Linux que está en los laboratorios.
	Saludos,
	Marcelo

	> Marcelo,
	> Queria saber si podemos usar comandos que solo son validos para linux
	> unicamente. Queremos agregarle colores a las letras, y para hacerlo
	> encontre un printf que cambia el color del texto, pero aparentemente
	> funciona en linux unicamente. El printf es el siquiente:
	> printf("%c[1;31m", 27);
	> Ese printf no imprime nada, y cambia el color de texto del programa a rojo
	>
	> Despues hay otro printf que lo que hace es limpiar la consola para que
	> quede vacia. Y pensabamos usarlo para evitar tener tantas impresiones del
	> tablero en la consola. El printf es el siguiente:
	> printf ("\033c");
	>
	> Pero de nuevo, creo que funciona unicamente en linux. Y antes de seguir
	> haciendo cambios me gustaria saber si podemos usar ambas, ya que hoy en
	> clase escuche que el archivo binario que creamos se puede levantar
	> unicamente desde linux, no de windows. Supuse que tambien podriamos usar
	> comandos que solo funcionen para linux. Saludos,
	> Ignacio
