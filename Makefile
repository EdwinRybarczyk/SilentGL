Compiler = gcc
srcDir = SilentGL/SilentGL/
BuildDir = Bin/
Output = SilentGLtest
Includedir = Include
srcFiles = $(srcDir)SilentRasterizer.c $(srcDir)SilentRenderer.c $(srcDir)SilentScreen.c $(srcDir)Source.c

compile:
	$(Compiler) $(srcFiles) -o $(BuildDir)$(Output)	-lSDL2


clean:
	rm -rf $(BuildDir)
