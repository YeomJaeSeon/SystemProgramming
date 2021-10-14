CC=gcc
OBJS=fileOpenClose.o
TARGET=fileOpenClose.out

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)
$(OBJS): fileOpenClose.c
	 $(CC) -c -o $@ fileOpenClose.c


clean:
	rm -f *.o
	rm -f $(TARGET)
