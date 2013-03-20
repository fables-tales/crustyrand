CFLAGS = -Wall -Werror -Wextra -pthread

.PHONY: analyse

crustyrand: build/sources/timersource.o build/main.o
	gcc $(CFLAGS) $^ -o $@


build/sources/timersource.o: src/sources/timersource.c
	gcc $(CFLAGS) -c $^ -o $@


build/main.o: src/main.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm -rf build/sources/timersource.o
	rm -rf build/main.o

analyse:
	python analysis/compute_ratio.py
	python analysis/uniformity.py
