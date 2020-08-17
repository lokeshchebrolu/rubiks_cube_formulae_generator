
TARGET=cube_formulae
CSRC=main.c cube.c matrix_operations.c movements.c print.c colour.c read.c
CSRC+=

CC=gcc
OPT=2
DEBUG=-ggdb3
CFLAGS=-Wall -Wno-switch $(DEBUG) -O$(OPT)
LDFLAGS=-lm

COBJ=$(CSRC:.c=.o)

all: $(TARGET)

$(TARGET): $(COBJ)
	@echo "linking ...."
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(COBJ): %.o: %.c
	@echo "compiling - $< ...."
	$(CC) -c $< $(CFLAGS)

clean:
	@echo "deleting generated files ...."
	rm -f $(TARGET) $(COBJ)

.PHONY: clean all
