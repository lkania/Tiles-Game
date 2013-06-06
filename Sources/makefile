install: BackEnd.c FrontEnd.c getnum.c tilesFront.h tilesBack.h getnum.h
	gcc -o Tiles-Game BackEnd.c FrontEnd.c getnum.c tilesFront.h tilesBack.h getnum.h -I.

clean:
	ls | grep -v "\.c" | grep -v "\.h" | grep -v makefile | xargs rm 

