all: histlib sample

# Create a statically linked library
histlib:
	cc -Wall -c ./src/histLib.cpp `pkg-config --cflags opencv` -I./include -o ./build/histlib.o
	ar rcs ./lib/libopencv_hist.a ./build/histlib.o

# Compile and link the sample code
sample:
	cc -c ./src/main.cpp `pkg-config --cflags opencv` -I./include -o ./build/sample.o
	cc ./build/sample.o `pkg-config --libs opencv` -L./lib -lopencv_hist -o ./sample

clean:
	rm ./build/*
	rm ./lib/*
	rm ./sample
