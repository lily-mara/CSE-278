EXAMPLE=example1.out
LAB=lab5.out

EXAMPLE : example1.asm
	nasm -felf32 -g example1.asm
	gcc -g example1.o -o $(EXAMPLE)

LAB : lab5.asm
	nasm -felf32 -g lab5.asm
	gcc -g lab5.o -o $(LAB)

.PHONY: clean
clean :
	rm -f *.out *.o
