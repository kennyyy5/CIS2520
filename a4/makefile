# Target to create the executable for assignment 3 question 1
a4: main.o graph_functions.o
	gcc main.o graph_functions.o -o a4

# Compile q1.o from q1.c
main.o: main.c graph.h
	gcc -Wall -std=c99 -c -g -pedantic main.c

# Compile q1_functions.o from q1_functions.c
graph_functions.o: graph_functions.c graph.h
	gcc -Wall -std=c99 -c -g -pedantic graph_functions.c

# Clean up the compiled objects and executables
clean:
	rm -f *.o graph