CC	= gcc
LD	= gcc

CFLAGS	= -g -Wall 
LDFLAGS	= libclaves.a
HEADERS = claves.h linked_list.h

PRGS	= cliente servidor

LIBS	= -lpthread -lrt

all: libclaves.a $(PRGS)

libclaves.a: claves.o
	ar -rv libclaves.a claves.o

cliente.o: cliente.c $(HEADERS)
	$(CC) $(CFLAGS) -c cliente.c $(LIBS)

servidor.o: servidor.c $(HEADERS)
	$(CC) $(CFLAGS) -c servidor.c $(LIBS)

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) -c linked_list.c 

cliente: cliente.o libclaves.a
	$(CC) $(CFLAGS) cliente.o libclaves.a -o cliente $(LIBS)

servidor: servidor.o linked_list.o
	$(CC) $(CFLAGS) servidor.o linked_list.o -o servidor $(LIBS)

clean:
	-rm -f *.o *.a *.out *~ $(PRGS)