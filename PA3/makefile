CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all	: cb
	@echo ""

cb : cycleBreaking.o main.o
	$(CC) $(OPTFLAGS) cycleBreaking.o main.o -o $@
main.o : src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
cycleBreaking.o : src/cycleBreaking.cpp src/cycleBreaking.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

.PHONY: clean
clean:
	rm *.o
	rm cb