do: clear bigintsub run
test: clear bigintsub test

bigintsub: main.o libs.o
	gcc -o bigintsub main.o libs.o

bigintsub.o: main.c libs.h
	gcc -c mian.c

libs.o: libs.c
	gcc -c libs.c

clear:
	rm bigintsub *.o

run:
	./bigintsub 10000000000000000000000000000000 1

test:
	./testy.sh