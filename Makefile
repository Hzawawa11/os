TARGET=	$1
SRCS=	$(TARGET).c
OBJS=	$(SRCS:.c=.o)
CC=	gcc
CFLAGS=	-O3 

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)

.c.o:
	$(CC) -c $< -o .o

debug:
	$(CC) -o $(BINDIR)$(TARGET)  -g $(SRCS) $(LDFLAGS) -O0

run:
	./$(TARGET)

clean:
	rm -rf 
