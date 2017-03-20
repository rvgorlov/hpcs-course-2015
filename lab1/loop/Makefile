loop := loop
loop_objs := loop.o hpctimer.o

perf1 := sudo perf stat -e branch-misses ./$(loop)
perf2 := sudo perf stat ./$(loop)
report := sudo perf record -e ./$(loop)


CC := gcc
CFLAGS := -O0 -Wall -g -std=c11
LDFLAGS :=

.PHONY: all clean

all: $(loop)

$(loop): $(loop_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

loop.o: loop.c
hpctimer.o: hpctimer.c hpctimer.h

clean:
	@rm -rf *.o $(loop)
