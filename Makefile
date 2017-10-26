src = src/*.{c,h}
out = bin/SilentGL

all:
	gcc $(src) -o $(out) -lSDL2

gitadd:
	git add $(src)
	git add $(out)
