CC=gcc
OBJS=stdoutFile.o
TARGET=stdoutFile.out

all : $(TARGET)

$(TARGET): $(OBJS)
	     $(CC) -o $@ $(OBJS)
$(OBJS): closeStdout.c
	 $(CC) -c -o $@ closeStdout.c

clean:
	rm -f *.o
	rm -f $(TARGET)

