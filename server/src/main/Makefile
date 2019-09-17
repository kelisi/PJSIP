# If your application is in a file named myapp.cpp or myapp.c
# this is the line you will need to build the binary.
all: canal

canal: main.c
		$(CC) -d -g -o $@ $< `pkg-config --cflags --libs libpjproject`

clean:
		rm -f main.o canal