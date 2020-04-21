all:
	g++ src/main.cc -O3 -o view.out `pkg-config opencv --cflags --libs`
debug:
	g++ src/main.cc -g -o view_debug.out `pkg-config opencv --cflags --libs`