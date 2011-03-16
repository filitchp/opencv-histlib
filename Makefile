all: histlib main

histlib:
	cc -Wall -c ./src/histLib.cpp `pkg-config --cflags opencv` -o ./build/histlib.o

main:
	cc -c ./src/main.cpp `pkg-config --cflags opencv` -o ./build/main.o
	cc ./build/main.o ./build/histlib.o `pkg-config --libs opencv` -o ./Sample

clean:
	rm ./build/*
