CC=gcc
OBJS=fileOpenClose.o
TARGET=fileOpenClose.out

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f *.txt

$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)

$(OBJS): fileOpenClose.c
	 gcc -c -o $@ fileOpenClose.c
