NAME		= cub3D

LIBFT		= libft/libft.a

MLX_DIR 	= minilibx_mms/
MLX_NAME	= libmlx.dylib
LIBFLAGS	= -lmlx

CC	= gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS		= -O2
DBGFLAGS	= -g

MLX			= $(addprefix $(MLX_DIR),$(MLX_NAME))
INCLUDES	= -I includes/ -I libft/includes/ -I $(MLX_DIR)
LIBFLAGS	+= -L libft -lft -L $(MLX_DIR)

override FLAGS ?= $(CFLAGS)

# check if fclean needed after last project building
CHECK_OBJS = fclean_keep_bmp

#--------- cub3D compiling -----------
SRCDIR		= src/
OBJDIR		= objs/
FLSDIR		=

FLS_1	= $(addprefix $(FLSDIR), \
			main \
			clearing \
			draw_back \
			draw_sprites \
			draw_vline \
			errors \
			parsing_conf \
			raycasting \
			start_game \
			keys \
			sprites \
			screenshot \
			texture )

FCLEAN_FLAG	= $(CHECK_OBJS)

SRC			= $(FLS_1)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

all: $(NAME)

$(NAME):		$(FCLEAN_FLAG) $(LIBFT) $(OBJ)
	@echo '----Making cub3D ------'
	$(CC)		$(FLAGS) $(OBJ) $(INCLUDES) $(LIBFLAGS) -o $(NAME)
	@echo "Ready"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p	$(OBJDIR)
	@$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@echo "$@ ready"

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

run: all
	./$(NAME) maps/default.cub

save: all
	./$(NAME) maps/default.cub --save

clean:
	rm -rf		$(OBJDIR)

clean_all: clean libft_clean

fclean:			clean
	rm -f		$(NAME)
	rm -f		screenshot*.bmp

fclean_keep_bmp: clean
	rm -f		$(NAME)

fclean_all: fclean libft_fclean mlx_fclean

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

$(LIBFT): libft_force_make
	@echo '---Making libft ------'
	@make		-C libft/ --no-print-directory
	@echo 'Making libft done'

libft_clean:
	make clean	-C libft/

libft_fclean:
	make fclean	-C libft/

libft_re:
	make re		-C libft/

norma:
	norminette ./src/ ./libft/srcs/*.c ./libft/includes/*.h ./includes/

re: fclean all

.PHONY: all \
		clean \
		clean_all \
		fclean \
		fclean_all \
		fclean_keep_bmp \
		debug \
		libft_clean \
		libft_fclean \
		libft_force_make \
		libft_re \
		mlx_clean \
		mlx_fclean \
		mlx_force_make \
		mlx_re \
		libs \
		re \
		run \
		save
