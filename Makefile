src = src/*.{c,h}
out = bin/SilentGL

all:
	gcc $(src) -o $(out) -lm -lSDL2 -lpthread

gitadd:
	git add $(src)
	git add $(out)
