FILES = src/main.c src/tools.c src/utils/parce_utils.c src/utils/map_utils.c src/utils/map_utils1.c src/utils/utils.c src/utils/utils1.c  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(FILES:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

MLX_FLAGS = -lm 

NAME = cub3d

all: $(NAME)

%.o: %.c header/cub.h
	@$(CC) -c $< -o $@
	
$(NAME): $(OBJ)
	@make -C ./libft
	@$(CC) $(OBJ) $(FLAGS) libft/libft.a -o $(NAME)

clean:
	@make -C ./libft clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C ./libft fclean
	@rm -rf $(NAME)

re: fclean all
