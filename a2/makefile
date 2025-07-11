# Target to create the executable for assignment 2 question 1
a2q1: q1.o q1_functions.o
	gcc q1.o q1_functions.o -o a2q1

# Target to create the executable for assignment 2 question 2
a2q2: q2.o q2_functions.o
	gcc q2.o q2_functions.o -o a2q2

# Compile q1.o from q1.c
q1.o: q1.c q1.h
	gcc -Wall -std=c99 -c -g -pedantic q1.c

# Compile q2.o from q2.c
q2.o: q2.c q2.h
	gcc -Wall -std=c99 -c -g -pedantic q2.c

# Compile q1_functions.o from q1_functions.c
q1_functions.o: q1_functions.c q1.h
	gcc -Wall -std=c99 -c -g -pedantic q1_functions.c

# Compile q2_functions.o from q2_functions.c
q2_functions.o: q2_functions.c q2.h
	gcc -Wall -std=c99 -c -g -pedantic q2_functions.c

# Clean up the compiled objects and executables
clean:
	rm -f *.o a2q1 a2q2
