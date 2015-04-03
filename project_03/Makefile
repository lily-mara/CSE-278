PREFIX=proj3
TARGET=$(PREFIX).out
ASM_SRC=$(PREFIX).asm
OBJ=$(PREFIX).o
CC=gcc
CC_OPTS=
ASM=nasm
ASM_OPTS=-felf32 -g


$(TARGET) : $(ASM_SRC)
	$(ASM) $(ASM_OPTS) $(ASM_SRC)
	$(CC) $(OBJ) -o $(TARGET)

.PHONY: clean
clean :
	rm -f *.out *.o

test : $(TARGET)
	python tests.py ./$(TARGET)
