C_SOURCES = $(wildcard frameworks/*.c *c)
HEADERS = $(wildcard frameworks/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}

MAIN = main
CC = gcc
CFLAGS = -Wall -g

run: ${MAIN}
	./${MAIN}
	$(MAKE) clean

main: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ -lm

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ -lm

clean:
	rm frameworks/*.o *.o ${MAIN}