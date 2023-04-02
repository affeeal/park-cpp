.PHONY: clean generate build hw2

clean:
	rm -rf build/ .cache/

generate:
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

build:
	cmake --build build

hw2:
	./build/hw2/hw2 \
		'echo 1 | cat file_1.txt | cat file_2.txt'
