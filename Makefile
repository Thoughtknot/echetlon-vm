CC=gcc
CFLAGS=-lm
DEPS = src/main.c src/instructions/instructions.c src/memory/memory.c
OBJ = src/main.o src/instructions/instructions.o src/memory/memory.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) -g -o echetlon $^ $(CFLAGS)

clean:
	rm -r src/*.o src/*/*.o
	rm echetlon