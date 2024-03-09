CC = gcc
CFLAGS = -Wall -Wextra

SRC = projet_Sokoban_D-TheProgrammer.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = projet_Sokoban_D-TheProgrammer

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

# supprimer quand cest windows
ifeq ($(OS),Windows_NT)
clean:
    rm -f $(OBJ) $(EXECUTABLE).exe
endif
