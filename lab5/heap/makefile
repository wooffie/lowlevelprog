	
test: build
		gcc -Wall -std=c11 -pedantic -Wextra -o test.exe test.c CuTest.c -L. -lHeap
		test.exe
		
build:
		gcc -c -Wall -std=c11 -pedantic -Wextra heap_main.c
		ar rsc libHeap.a heap_main.o
		
main: build
		gcc -Wall -std=c11 -pedantic -Wextra -o heap.exe main.c -L. -lHeap
		
		
clean:
		del -f *.o *.a *.exe
		