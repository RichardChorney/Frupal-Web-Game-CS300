CFLAGS = -Wall -pedantic

all:
	g++ $(CFLAGS) -static *.cpp -o frupal
mac:
	g++ $(CFLAGS) *.cpp -o frupal

clean:
	rm -f frupal
