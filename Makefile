.PHONY: clean generate build hw2

clean:
	rm -rf build/ .cache/

generate:
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

silent-build:
	cmake --build build/

build:
	@make -s silent-build 

hw2:
	./build/hw2/hw2 \
		'echo 1 | cat README.md | cat Makefile | head 8'
