CFLAGS = -Wall -pedantic

all:
	g++ $(CFLAGS) -static *.cpp -o frupalCGI.cgi
mac:
	g++ $(CFLAGS) *.cpp -o frupal

clean:
	rm -f frupal
