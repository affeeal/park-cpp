.PHONY: clean generate build hw1

clean:
	rm -rf build/

generate:
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

build:
	cmake --build build

hw1:
	./build/hw1/hw1 \
		"Alfred Hitchcock" \
		hw1/.files/name.basics.tsv \
		hw1/.files/title.akas.tsv \
		hw1/.files/title.basics.tsv \
		hw1/.files/title.crew.tsv
