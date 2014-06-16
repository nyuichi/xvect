CFLAGS += -g -O0 -Wall

all: clean t/main
	t/main

clean:
	rm -rf t/main
