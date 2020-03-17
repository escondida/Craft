MKSHELL = rc

TARGS = craft

<config.mk

craft: src
	install src/$target $target

src:V:
	cd src; mk; cd ..

clean:V:
	rm -f craft src/craft src/*.o
