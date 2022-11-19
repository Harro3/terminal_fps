CC= gcc
CFLAGS= -Wall -Werror -Wvla -Wextra -pedantic -std=c99 -g
LDFLAGS=-lcriterion -lm

SRC= src/screen.c src/rendering.c src/map.c
OBJ=$(SRC:.c=.o)

all: clean main

test_unit:
	$(CC) $(CFLAGS) -fsanitize=address -o test $(SRC) tests/unit/tests.c $(LDFLAGS)
	./test --verbose

check: test_unit

main:
	CFLAGS+=-fsanitize=address
	$(CC) $(CFLAGS) -o main $(SRC) src/main.c $(LDFLAGS)

clean:
	$(RM) *.log
	$(RM) test
	$(RM) main
	$(RM) test_socket
	$(RM) httpd
