CC=gcc
all:
	$(CC) example.c ops_limiter.c -o example
clean:
	rm -f example
