CC=gcc
TARGET=result.out
OBJ=Lab1_2.o
SOURCE=Lab1_2.c

all: $(TARGET)

$(TARGET): $(OBJ)
	     $(CC) -o $@ $(OBJ)
$(OBJ): $(SOURCE)
	  $(CC) -c -o $@ $(SOURCE)

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f $(OBJ)
