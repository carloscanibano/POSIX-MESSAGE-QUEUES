CC	= gcc
LD	= gcc

CFLAGS	= -g -Wall
LDFLAGS	= libclaves.a
PRGS	= cliente1 cliente2 cliente3 cliente4 cliente5 cliente6 servidor
LIBS	= -lpthread -lrt

all: libclaves.a $(PRGS)

libclaves.a: claves.o
	ar -rv libclaves.a claves.o

cliente1.o: cliente1.c
	$(CC) $(CFLAGS) -c cliente1.c

cliente2.o: cliente2.c
	$(CC) $(CFLAGS) -c cliente2.c

cliente3.o: cliente3.c
	$(CC) $(CFLAGS) -c cliente3.c

cliente4.o: cliente4.c
	$(CC) $(CFLAGS) -c cliente4.c

cliente5.o: cliente5.c
	$(CC) $(CFLAGS) -c cliente5.c

cliente6.o: cliente6.c
	$(CC) $(CFLAGS) -c cliente6.c

servidor.o: servidor.c
	$(CC) $(CFLAGS) -c servidor.c

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) -c linked_list.c

cliente1: cliente1.o libclaves.a
	$(CC) $(CFLAGS) cliente1.o libclaves.a -o cliente1 $(LIBS)

cliente2: cliente2.o libclaves.a
	$(CC) $(CFLAGS) cliente2.o libclaves.a -o cliente2 $(LIBS)

cliente3: cliente3.o libclaves.a
	$(CC) $(CFLAGS) cliente3.o libclaves.a -o cliente3 $(LIBS)

cliente4: cliente4.o libclaves.a
	$(CC) $(CFLAGS) cliente4.o libclaves.a -o cliente4 $(LIBS)

cliente5: cliente5.o libclaves.a
	$(CC) $(CFLAGS) cliente5.o libclaves.a -o cliente5 $(LIBS)

cliente6: cliente6.o libclaves.a
	$(CC) $(CFLAGS) cliente6.o libclaves.a -o cliente6 $(LIBS)

servidor: servidor.o linked_list.o
	$(CC) $(CFLAGS) servidor.o linked_list.o -o servidor $(LIBS)

clean:
	-rm -f *.o *.a *.out *~ $(PRGS)
