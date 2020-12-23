CC=clang
ODIR=build

all: prime

prime: prime.c
	$(CC) -o $(ODIR)/prime.out prime.c -lm

clean:
	find $(ODIR) -type f -delete