CC=gcc
TARGET=Lab2_2.out
OBJ=Lab2_2.o
SOURCE=Lab2_2.c

all: $(TARGET)

$(TARGET): $(OBJ)
	     $(CC) -o $@ $(OBJ)
$(OBJ): $(SOURCE)
	  $(CC) -c -o $@ $(SOURCE)

clean:
	rm -f *.o
	rm -f $(TARGET)
