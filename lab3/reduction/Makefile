prog := prog
prog_objs := prog.o hpctimer.o

CC := gcc
CFLAGS := -Wall -O2 -mavx
LDFLAGS := 

.PHONY: all clean

all: $(prog)

$(prog): $(prog_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

prog.o: prog.c
hpctimer.o: hpctimer.c hpctimer.h

clean:
	@rm -rf *.o $(prog)
