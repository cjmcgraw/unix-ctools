str: src/show.c src/trim.c src/main.c src/split.c src/utils.c build
	gcc -g3 -o build/str src/utils.c src/split.c src/trim.c src/show.c src/main.c

build:
	mkdir build

install: build/str
	cp ./build/str /usr/local/bin/str

clean:
	rm -rf build
