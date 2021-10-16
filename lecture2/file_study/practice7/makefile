CC=gcc
TARGET=main.out
OBJS=main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)
$(OBJS): main.c
	 $(CC) -c -o $@ main.c

clean:
	rm -f *.o
	rm -f $(TARGET)
