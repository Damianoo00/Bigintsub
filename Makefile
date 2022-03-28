all: bigintsub
do: bigintsub run
test: bigintsub test

bigintsub: main.o libs.o
	gcc -o bigintsub main.o libs.o

bigintsub.o: main.c libs.h
	gcc -c mian.c

libs.o: libs.c flags.h
	gcc -c libs.c

clear:
	rm bigintsub *.o

run:
	./bigintsub -10000000 -7

test:
	./testy.sh