CC=gcc
CFLAGS=g
OUT=build

.PHONY: run clean

run: list hello
	$(OUT)/list

hello: hello.c
	$(CC) -$(CFLAGS) -o $(OUT)/hello hello.c

list: list.c
	$(CC) -$(CFLAGS) -o $(OUT)/list list.c

clean:
	-rm list $(objects)
