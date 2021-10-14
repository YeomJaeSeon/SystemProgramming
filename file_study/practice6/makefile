CC=gcc
TARGET=result.out
OBJ=result.o

all: $(TARGET)

$(TARGET): $(OBJ)
	     $(CC) -o $@ $(OBJ)
$(OBJ): read.c
	$(CC) -c -o $@ read.c

clean:
	rm -f *.o
	rm -f $(TARGET)
