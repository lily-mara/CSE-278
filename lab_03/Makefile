CC=clang
OPTS=-ggdb
COMP=$(CC) $(OPTS)

FILES=lab3.c
EXECUTABLE=lab3.out

$(EXECUTABLE) : $(FILES)
	$(COMP) -o $(EXECUTABLE) $(FILES)

clean :
	rm -f $(EXECUTABLE) *.o
