# Makefile para TP Corrector de texto

ARCHIVOS.O =  main.o glist.o hash_table.o utils.o word_functions.o dict.o io.c
FLAGS = -Wall -Wextra -Werror -std=c99
	
main: $(ARCHIVOS.O)  
	gcc -o $@ $^ $(FLAGS)

main.o: main.c 
	gcc -c $< $(FLAGS)	

word.o: word_functions.c 
	gcc -c $< $(FLAGS)

dict.o: dict.c 
	gcc -c $< $(FLAGS)

hash.o: hash_table.c 
	gcc -c $< $(FLAGS)

glist.o: glist.c 
	gcc -c $< $(FLAGS)

utils.o: utils.c 
	gcc -c $< $(FLAGS)

io.o: io.c
	gcc -c $< $(FLAGS)
	
clean:
	rm *.o
	rm main

.PHONY = clean