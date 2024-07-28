run:
	gcc -o a.out main.c ui.c game.c -Wall `pkg-config sdl2 --cflags --libs`	
	./a.out
