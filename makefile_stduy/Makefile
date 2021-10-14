TARGET= result.out
CC= gcc
OBJS= main.o foo.o bar.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: foo.h bar.h main.c
foo.o: foo.h foo.c
bar.o: bar.h bar.c

clean:
	rm -f *.o
	rm -f $(TARGET)
	
