CFLAGS = -Wall -Werror -Wextra -pthread -lgmp -O2

.PHONY: analyse

crustyrand: build/sources/timersource.o build/entropy_pool.o build/main.o
	gcc $(CFLAGS) $^ -o $@


build/sources/timersource.o: build/sources src/sources/timersource.c
	gcc $(CFLAGS) -c $^ -o $@

build/entropy_pool.o: src/entropy_pool.c
	gcc $(CFLAGS) -c $^ -o $@

build/main.o: src/main.c
	gcc $(CFLAGS) -c $^ -o $@

build/sources:
	mkdir -p build/sources

clean:
	rm -rf build/sources/timersource.o
	rm -rf build/*.o

analyse:
	python analysis/compute_ratio.py
	python analysis/uniformity.py
