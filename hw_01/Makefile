FILES=average.asm
EXECUTABLE=average.out

$(EXECUTABLE) : $(FILES)
	nasm -faout $(FILES)
	ld average.o -o $(EXECUTABLE)

clean :
	rm -f $(EXECUTABLE) *.o
