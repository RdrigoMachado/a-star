CC=g++
CFLAGS=
CODIGOS=main.cpp utils.cpp estruturas.cpp
ALGORITMOS=algoritmos/astar.cpp
EXECUTAVEL=main



all:clear clean $(EXECUTAVEL)
$(EXECUTAVEL): $(EXECUTAVEL).cpp
				$(CC) $(CFLAGS) -o $(EXECUTAVEL) $(CODIGOS) $(ALGORITMOS)

debug: clear clean $(EXECUTAVEL)_debug
$(EXECUTAVEL)_debug: $(EXECUTAVEL).cpp
				$(CC) -D_debug $(CFLAGS) -o $(EXECUTAVEL) $(CODIGOS) $(ALGORITMOS)

clear:
	clear
clean:
	rm -f main