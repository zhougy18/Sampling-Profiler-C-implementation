CC=gcc
CFLAGS=-I. -lunwind -lunwind-x86_64
DEPS = hotspots_sampling.h
OBJ = main.o hotspots_sampling.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
