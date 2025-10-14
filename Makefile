FILES = src/main.c src/utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -lm 

NAME = cub3d

all: $(NAME)

%.o: %.c header/cub.h
	@$(CC) -c $< -o $@
	
$(NAME): $(OBJ)
	@make -C ./libft
	@$(CC) $(OBJ) libft/libft.a -fsanitize=address -g3 -o $(NAME)

clean:
	@make -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all
