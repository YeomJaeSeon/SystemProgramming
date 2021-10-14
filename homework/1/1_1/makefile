CC=gcc
OBJS=Lab1_1.o
TARGET=Lab1_1.out
SOURCE=Lab1_1.c

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)
$(OBJS): $(SOURCE)
	 $(CC) -c -o $@ $(SOURCE)
