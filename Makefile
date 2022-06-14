capslockmon: capslockmon.c Makefile
	gcc -Wno-deprecated-declarations capslockmon.c -o capslockmon `pkg-config --libs --cflags gtk+-3.0` -lX11

