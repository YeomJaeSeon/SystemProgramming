CC=gcc
OBJS=fileReadWrite.o
TARGET=fileReadWrite.out

all: $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)
$(OBJS): fileReadWrite.c
	 $(CC) -c -o $@ fileReadWrite.c

clean: 
	rm -f *.o
	rm -f $(TARGET)
