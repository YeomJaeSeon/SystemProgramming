CC=gcc
TARGET=Lab2_1.out
OBJ=Lab2_1.o
SOURCE=Lab2_1.c

all: $(TARGET)

$(TARGET): $(OBJ)
	     $(CC) -o $@ $(OBJ)
$(OBJ): $(SOURCE)
	  $(CC) -c -o $@ $(SOURCE)

clean:
	rm -f *.o
	rm -f $(TARGET)
