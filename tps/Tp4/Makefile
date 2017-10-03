CC = gcc
CFLAGS = -g -Wall
TARGETS = tp4
all: $(TARGETS)

tp4: tpserver.c http.c solicitud.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o
