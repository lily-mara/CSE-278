CC=clang
OPTS=-ggdb -std=c99
COMP=$(CC) $(OPTS)

FILES=proj1.c main.h
EXECUTABLE=proj1.out

$(EXECUTABLE) : $(FILES)
	$(COMP) -o $(EXECUTABLE) $(FILES)

clean :
	rm -f $(EXECUTABLE) *.o
