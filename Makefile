build : DNASim.exe
DNASim.exe : main.o CmdStack.o
	gcc main.o CmdStack.o -o DNASim.exe
main.o : main.c	
	gcc -c -g main.c
CmdStack.o : CmdStack.c
	gcc -c -g CmdStack.c
clean :
	rm *.o DNASim.exe

