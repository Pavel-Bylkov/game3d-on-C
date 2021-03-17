NAME	= Cub3D

LIBFT	= ./Libft/libft.a
MLX		= ./minilibx_mms/libmlx.dylib
MLX_DIR = ./minilibx_mms/

COMP	= gcc
FLAG_GCC = -Wall -Wextra -Werror

CUB_FUNC = main.c \
			parsing_conf.c \
			clearing_data.c \
			errors.c \
			texture.c \
			get_next_line.c get_next_line_utils.c

SOURCES = src
OBJ = objects

FILES_C = $(addprefix $(SOURCES)/,$(CUB_FUNC))
FILES_O = $(addprefix $(OBJ)/,$(CUB_FUNC:.c=.o))

FLAG_MLX = -framework OpenGL -framework Appkit

INCLUDES = -I includes/ -I $(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(FILES_O)
	@$(COMP) $(MLX) $(FLAG_MLX) $(FILES_O) $(INCLUDES) $(LIBFT) -o $(NAME)
	@echo "Ready"

$(OBJ)/%.o : $(SOURCES)/%.c
	@mkdir -p $(OBJ)
	@$(COMP) $(FLAG_GCC) -o $@ -c $^
	@echo "$@ ready"

$(LIBFT):
	@make -C Libft/
	@echo 'Making libft done'

$(MLX):
	@make -C $(MLX_DIR)
	@echo 'Making minilibx done'

run: all
	./$(NAME) ./maps/map1.cub

save: all
	./$(NAME) ./maps/map1.cub --save

norma:
	norminette ./src/ ./libft/*.c ./libft/*.h ./includes/

clean:
	@rm -f $(FILES_O)
	@rm -rf $(OBJ)
	@make clean -C ./libft
	@make clean -C $(MLX_DIR)
	@echo "O-files deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -rf *.bmp
	@make fclean -C ./libft
	@echo "All files delete"

re: fclean all

.PHONY: clean fclean all re
