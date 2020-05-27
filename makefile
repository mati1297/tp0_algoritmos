CC = g++-7
CFLAGS  = -pedantic -Wall


default: imagen clean

imagen:  main.o leer_cmdline.o imagen.o cmdline.o
	$(CC) $(CFLAGS) -o imagen main.o leer_cmdline.o imagen.o cmdline.o

main.o: main.cpp imagen.h leer_cmdline.h cmdline.h
	$(CC) $(CFLAGS) -g -c main.cpp

leer_cmdline.o:  leer_cmdline.cpp leer_cmdline.h cmdline.h imagen.h
	$(CC) $(CFLAGS) -g -c leer_cmdline.cpp

imagen.o:  imagen.cpp imagen.h
	$(CC) $(CFLAGS) -g -c imagen.cpp


cmdline.o:  cmdline.cpp cmdline.h
	$(CC) $(CFLAGS) -g -c cmdline.cpp

clean: 
	$(RM) count *.o *~
