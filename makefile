CC = gcc
CFLAGS = -Wall -Wextra
TARGET = multi_matrices
SRC = mm_clasico.c multi_matriz.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ) $(TARGET)
