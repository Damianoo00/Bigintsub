CC = gcc

hDIR = libs
cDIR = src
oDIR = obj
tDIR = tests

all: bigintsub
do: bigintsub run
test: bigintsub test

bigintsub: main.o bignumsub.o exceptions.o
	gcc -o bigintsub $(oDIR)/main.o $(oDIR)/bignumsub.o $(oDIR)/exceptions.o

main.o: $(cDIR)/main.c $(hDIR)/bignumsub.h
	$(CC) -c $(cDIR)/main.c 
	mv main.o $(oDIR)/main.o

bignumsub.o: $(cDIR)/bignumsub.c $(hDIR)/exceptions.h
	$(CC) -c $(cDIR)/bignumsub.c
	mv bignumsub.o $(oDIR)/bignumsub.o

exceptions.o: $(cDIR)/exceptions.c $(hDIR)/flags.h
	$(CC) -c $(cDIR)/exceptions.c
	mv exceptions.o $(oDIR)/exceptions.o

clear:
	rm bigintsub $(oDIR)/*.o

run:
	./bigintsub -10000000 -7

test:
	$(tDIR)/testy.sh