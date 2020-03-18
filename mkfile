MKSHELL = rc

TARGS = craft

<config.mk

craft: src/game
	install $prereq $target

src/game:
	cd src; mk; cd ..

clean:V:
	rm -f craft src/game src/*.o
