.PHONY: dev
dev:
	mkdir -p build && gcc -o build/my_sh src/main.c && cd build && ./my_sh

.PHONY: build
build:
	mkdir -p build && gcc -o build/my_sh src/main.c

.PHONY: help
help:
	cd help && python3 build_help.py