default: all

concurrency2:
	gcc -mrdrnd -pthread -g main.c concurrency2.c -o concurrency2

test: 
	gcc -mrdrnd -pthread -g concurrency2.c test_concurrency2.c -o test

all: concurrency2 test

clean:
	rm -f concurrency2 test

.PHONY: all show clean ps pdf showps
