CC = gcc
LDLIBS=-pthread
CFLAGS = -g -Wall
TARGETS = tp5
all: $(TARGETS)

tp5: tpserver.c http.c solicitud.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o
