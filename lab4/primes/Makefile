primes := primes
primes_objs := primes.o

CC := gcc
CFLAGS := -O0 -Wall -g -fopenmp
LDFLAGS := -fopenmp -lm

.PHONY: all clean

all: $(primes) 

$(primes): $(primes_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

primes.o: primes.c 

clean:
	@rm -rf *.o $(primes)
