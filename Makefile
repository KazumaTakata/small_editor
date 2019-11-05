all: build 

build: sample.c term.h raw_mode.h process.h 
	$(CC)  -g sample.c  -Wall -W -pedantic -std=c99

clean:
	rm a.out 
