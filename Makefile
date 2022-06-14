capslockmon: capslockmon.c
	gcc capslockmon.c -o capslockmon `pkg-config --libs --cflags gtk+-3.0` -lX11

