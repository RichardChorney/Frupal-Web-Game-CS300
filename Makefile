CFLAGS = -Wall -pedantic

frupal:
	g++ $(CFLAGS) *.cpp -o frupal

clean:
	rm -f frupal
