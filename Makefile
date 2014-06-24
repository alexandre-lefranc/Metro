# Fichier Makefile : instructions de compilation

# Declaration des variables

CC = gcc

CFLAGS = -Wall -pedantic -gstabs -ansi -Werror

SOURCE_DIR = src
OBJECT_DIR = obj
INCLUDE_DIR = inc

OFILES = $(OBJECT_DIR)/pile.o 			 \
         $(OBJECT_DIR)/graph.o         	 \
         $(OBJECT_DIR)/metro_interface.o \
         $(OBJECT_DIR)/metro_data.o		 \
         $(OBJECT_DIR)/metro_dijkstra.o  \
		 $(OBJECT_DIR)/metro_main.o		 


LIBS = -L/usr/X11R6/lib -lX11 -lXpm -lm

EXE = metro

# Regles de dependances

but : $(EXE)

$(OBJECT_DIR)/pile.o : $(SOURCE_DIR)/pile.c $(INCLUDE_DIR)/pile.h
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $(OBJECT_DIR)/pile.o $(SOURCE_DIR)/pile.c

$(OBJECT_DIR)/graph.o : $(SOURCE_DIR)/graph.c $(INCLUDE_DIR)/graph.h
	$(CC) -c -o $(OBJECT_DIR)/graph.o $(SOURCE_DIR)/graph.c

$(OBJECT_DIR)/metro_data.o : $(SOURCE_DIR)/metro_data.c $(INCLUDE_DIR)/metro_data.h $(INCLUDE_DIR)/metro_main.h $(INCLUDE_DIR)/metro_interface.h
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $(OBJECT_DIR)/metro_data.o $(SOURCE_DIR)/metro_data.c

$(OBJECT_DIR)/metro_interface.o : $(SOURCE_DIR)/metro_interface.c $(INCLUDE_DIR)/metro_interface.h $(INCLUDE_DIR)/metro_main.h $(INCLUDE_DIR)/graph.h $(INCLUDE_DIR)/metro_dijkstra.h
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $(OBJECT_DIR)/metro_interface.o $(SOURCE_DIR)/metro_interface.c

$(OBJECT_DIR)/metro_dijkstra.o : $(SOURCE_DIR)/metro_dijkstra.c $(INCLUDE_DIR)/metro_dijkstra.h $(INCLUDE_DIR)/metro_interface.h $(INCLUDE_DIR)/metro_data.h $(INCLUDE_DIR)/pile.h $(INCLUDE_DIR)/metro_main.h
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $(OBJECT_DIR)/metro_dijkstra.o $(SOURCE_DIR)/metro_dijkstra.c

$(OBJECT_DIR)/metro_main.o : $(SOURCE_DIR)/metro_main.c $(INCLUDE_DIR)/metro_main.h $(INCLUDE_DIR)/metro_data.h $(INCLUDE_DIR)/metro_interface.h $(INCLUDE_DIR)/metro_dijkstra.h
	$(CC) $(CFLAGS) -c -o $(OBJECT_DIR)/metro_main.o $(SOURCE_DIR)/metro_main.c

$(EXE) : $(OFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OFILES) $(LIBS)

clean :
	-rm -f $(OFILES)

.PHONY : but clean


# Fin du fichier Makefile 
# EOF
