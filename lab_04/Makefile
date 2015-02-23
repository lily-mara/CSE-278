TARGET=lab4.out

$(TARGET) : lab4.c
	gcc -o $(TARGET) lab4.c

lab4.s : lab4.c
	gcc -S  -fno-asynchronous-unwind-tables -masm=intel lab4.c

run : $(TARGET)
	./$(TARGET)
