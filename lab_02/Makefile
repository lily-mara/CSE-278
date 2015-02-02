CC=clang
OPTS=-ggdb
COMP=$(CC) $(OPTS)

FILES=lab2.c
EXECUTABLE=lab2.out

$(EXECUTABLE) : $(FILES)
	$(COMP) -o $(EXECUTABLE) $(FILES)

clean :
	rm -f $(EXECUTABLE) *.o
