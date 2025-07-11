# Target to create the executable for assignment 3 question 1
a3q1: a3q1_main.o a3q1_functions.o
	gcc a3q1_main.o a3q1_functions.o -o a3q1

# Target to create the executable for assignment 3 question 2
a3q2: a3q2_main.o a3q2_functions.o
	gcc a3q2_main.o a3q2_functions.o -o a3q2

# Compile q1.o from q1.c
a3q1_main.o: a3q1_main.c a3q1_header.h
	gcc -Wall -std=c99 -c -g -pedantic a3q1_main.c

# Compile q2.o from q2.c
a3q2_main.o: a3q2_main.c a3q2_header.h
	gcc -Wall -std=c99 -c -g -pedantic a3q2_main.c

# Compile q1_functions.o from q1_functions.c
a3q1_functions.o: a3q1_functions.c a3q1_header.h
	gcc -Wall -std=c99 -c -g -pedantic a3q1_functions.c

# Compile q2_functions.o from q2_functions.c
a3q2_functions.o: a3q2_functions.c a3q2_header.h
	gcc -Wall -std=c99 -c -g -pedantic a3q2_functions.c

# Clean up the compiled objects and executables
clean:
	rm -f *.o a3q1 a3q2