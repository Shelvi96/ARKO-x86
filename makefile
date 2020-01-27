main: main.o x86.o
	cc -m32 -o main main.o x86.o
	
main.o:
	cc  -m32 -std=c99 -c main.c

x86.o:
	nasm -f elf32 x86.s

clean:
	@echo "Removing unnecessary files..."
	rm main.o
	rm x86.o
	rm main
	@echo "Done."
