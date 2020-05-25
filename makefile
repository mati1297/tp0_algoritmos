CC = g++-7
CFLAGS  = -pedantic -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: imagen clean


imagen:  main.o argumentos_cmdline.o imagen.o aux_functions.o cmdline.o
	$(CC) $(CFLAGS) -o imagen main.o argumentos_cmdline.o imagen.o aux_functions.o cmdline.o

main.o: main.cpp imagen.h argumentos_cmdline.h cmdline.h
	$(CC) $(CFLAGS) -c main.cpp

argumentos_cmdline.o:  argumentos_cmdline.cpp argumentos_cmdline.h cmdline.h imagen.h
	$(CC) $(CFLAGS) -c argumentos_cmdline.cpp

imagen.o:  imagen.cpp imagen.h aux_functions.h
	$(CC) $(CFLAGS) -c imagen.cpp


aux_functions.o:  aux_functions.cpp aux_functions.h
	$(CC) $(CFLAGS) -c aux_functions.cpp


cmdline.o:  cmdline.cpp cmdline.h
	$(CC) $(CFLAGS) -c cmdline.cpp


clean: 
	$(RM) count *.o *~
