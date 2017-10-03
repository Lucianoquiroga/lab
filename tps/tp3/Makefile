CC=gcc
CFLAGS=-g -Wall
TARGETS=tp3

all: $(TARGETS)

tp3: tp3.c parser.c proc.c
	$(CC) $(CFLAGS) -o $@ $^

test: tp3
	cat noticia.txt | ./tp3

format-text:
	fold -w 80 -s noticia.txt > noticia2.txt
	#fmt -w 80 noticia > noticia2

justify-text:
	par 80j < noticia2.txt > noticia-formatted.txt
	rm -fv noticia2.txt

clean:
	rm -f *~ .o $(TARGETS) noticia2.txt


