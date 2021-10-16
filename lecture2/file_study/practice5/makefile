CC=gcc
OBJS=offset.o
TARGET=offset.out

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)
$(OBJS): offset.c
	 $(CC) -c -o $@ offset.c

clean:
	rm -f *.o
	rm -f $(TARGET)
