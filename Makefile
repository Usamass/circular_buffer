CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
BUFF_OBJ=circular.o
MAIN_OBJ=main.o
BUFF_SRC=src/circular_buffer.c
MAIN_SRC=main.c
EXEC=cb
all: $(EXEC)

$(EXEC): $(MAIN_OBJ) $(BUFF_OBJ)
	$(CC) -o $(EXEC) $(MAIN_OBJ) $(BUFF_OBJ)
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) -c $(MAIN_SRC) -o $(MAIN_OBJ)

$(BUFF_OBJ): $(BUFF_SRC)
	$(CC) -c $(BUFF_SRC) -o $(BUFF_OBJ)

clean:
	rm -rf $(EXEC) $(BUFF_OBJ) $(MAIN_OBJ)


