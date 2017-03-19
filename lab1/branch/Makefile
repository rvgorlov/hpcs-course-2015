branch := branch
branch_objs := branch.o hpctimer.o
perf1 := sudo perf stat -e branch-misses ./$(branch)
perf2 := sudo perf stat ./$(branch)
report := sudo perf record -e ./$(branch)

CC := gcc
CFLAGS := -O2 -Wall -g -std=c11
LDFLAGS :=

.PHONY: all clean

all: $(branch)

$(branch): $(branch_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

branch.o: branch.c
hpctimer.o: hpctimer.c hpctimer.h

clean:
	@rm -rf *.o $(branch)

test: all
	$(perf2)

report: all
	$(report)