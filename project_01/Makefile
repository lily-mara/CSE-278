CC=clang
OPTS=-ggdb -std=c99
COMP=$(CC) $(OPTS)

FILES=proj1.c
EXECUTABLE=proj1.out

$(EXECUTABLE) : $(FILES) main.h
	$(COMP) -o $(EXECUTABLE) $(FILES)

clean :
	rm -f $(EXECUTABLE) *.o
