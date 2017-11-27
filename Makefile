CFLAGS = -Wall -pedantic -static

all:
	g++ $(CFLAGS) *.cpp -o frupal

clean:
	rm -f frupal
