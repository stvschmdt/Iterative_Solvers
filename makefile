CC = gcc

CFLAGS = -Wall -std=c99 -O3

LDFLAGS = -lm

program = solvers

source = \
	 main.c \
	 init.c \
         jacobi.c \
	 gsm.c \
	 sor.c \

obj = $(source:.c=.o)

$(program): $(obj) solvers.h
	        $(CC) $(CFLAGS) $(obj) -o $@ $(LDFLAGS)

%.o: %.c
	        $(CC) $(CFLAGS) -c $< -o $@

clean:
	        rm -f $(program) $(obj) *.txt
run:
	        ./$(program)
edit:
	        vim -p $(source) solvers.h
