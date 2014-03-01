CC=g++
CFLAG=-lm
program=main 
all: $(program)
main: main.o
	$(CC) $(CFLAG) -o $@ main.o
main_release: main_release.o
	$(CC) $(CFLAG) -o $@ main_release.o -O3
main_debug: main_debug.o
	$(CC) $(CFLAG) -o $@ main_debug.o -g
main_prof: main_prof.o
	$(CC) $(CFLAG) -o $@ main_prof.o -pg
main.o: main.cpp
	$(CC) $(CFLAG) -c -o $@ main.cpp
main_release.o: main.cpp
	$(CC) $(CFLAG) -c -o $@ main.cpp -O3
main_debug.o: main.cpp
	$(CC) $(CFLAG) -c -o $@ main.cpp -g
main_prof.o: main.cpp
	$(CC) $(CFLAG) -c -o $@ main.cpp -pg
clean:
	rm -fr *.o main main_release main_debug main_prof
