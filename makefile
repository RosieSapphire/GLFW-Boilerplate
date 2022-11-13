CC=gcc
INC=-Iinclude -I/usr/include
LIB=-lglfw -lcglm -ldl -lpthread -lm

CFLAGS=-std=c99 -Wall -Wextra -Werror

SRC=main.c glad.c file.c mesh.c mat4.c
OBJ=main.o glad.o file.o mesh.o mat4.o

BIN=EXECUTABLE_NAME_HERE

all: CFLAGS += -O2
all: $(OBJ)
	clear
	rm -rf $(BIN) test *.o
	$(CC) $(CFLAGS) $(INC) -o $(BIN) $(addprefix src/,$(SRC)) -L. -Llib $(LIB)
	rm -rf *.o

run: CFLAGS += -O2
run: $(OBJ)
	clear
	rm -rf $(BIN) test *.o
	$(CC) $(CFLAGS) $(INC) -o $(BIN) $(addprefix src/,$(SRC)) -L. -Llib $(LIB)
	rm -rf *.o
	./$(BIN)

gdb: CFLAGS += -Og -ggdb3 -D DEBUG
gdb: $(OBJ)
	clear
	rm -rf $(BIN) test *.o
	$(CC) $(CFLAGS) $(INC) -o $(BIN) $(addprefix src/,$(SRC)) -L. -Llib $(LIB)
	rm -rf *.o
	gdb ./$(BIN) --tui

%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -c $^ $(LIB)

clean:
	rm -rf $(BIN) test *.o
	clear
