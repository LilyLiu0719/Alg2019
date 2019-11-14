CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all	: mps
	@echo ""

mps : maxPlanarSubset.o main.o
	$(CC) $(OPTFLAGS) maxPlanarSubset.o main.o -o $@
main.o : src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
maxPlanarSubset.o : src/maxPlanarSubset.cpp src/maxPlanarSubset.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

.PHONY: clean
clean:
	rm *.o
	rm mps