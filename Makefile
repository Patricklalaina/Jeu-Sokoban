NAME = sokoban

SRC = $(wildcard ./src/*.c)

CFLAGS = #-Wall -Werror -Wextra -g

OBJ = $(SRC:.c=.o)

CC = cc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

run: all clean
	@./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean run
