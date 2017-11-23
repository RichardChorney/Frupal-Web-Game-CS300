CFLAGS = -Wall -pedantic

all:
	g++ $(CFLAGS) *.cpp -o frupal

clean:
	rm -f frupal
