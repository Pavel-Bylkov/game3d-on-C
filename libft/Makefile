NAME = libft.a

H = libft.h

# School uses 'clang' for testing, so better check it as well. Just in case.
COMPILER = gcc

FLAGS = -Wall -Wextra -Werror

SRC = \
        ft_atoi.c \
        ft_bzero.c \
        ft_calloc.c \
        ft_isalnum.c \
        ft_isalpha.c \
        ft_isascii.c \
        ft_isdigit.c \
        ft_isprint.c \
        ft_itoa.c \
        ft_memccpy.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_memcpy.c \
        ft_memmove.c \
        ft_memset.c \
        ft_putchar_fd.c \
        ft_putendl_fd.c \
        ft_putnbr_fd.c \
        ft_putstr_fd.c \
        ft_split.c \
        ft_strchr.c \
        ft_strdup.c \
        ft_strjoin.c \
        ft_strlcat.c \
        ft_strlcpy.c \
        ft_strlen.c \
        ft_strmapi.c \
        ft_strncmp.c \
        ft_strnstr.c \
        ft_strrchr.c \
        ft_strtrim.c \
        ft_substr.c \
        ft_tolower.c \
        ft_toupper.c

SRC_BONUS = \
         ft_lstadd_back.c \
         ft_lstadd_front.c \
         ft_lstclear.c \
         ft_lstdelone.c \
         ft_lstiter.c \
         ft_lstlast.c \
         ft_lstmap.c \
         ft_lstnew.c \
         ft_lstsize.c

OBJ = $(SRC:%.c=%.o)

OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

all: $(NAME)

# each single object files depends only on single source file and header
%.o : %.c $(H)
	@$(COMPILER) $(FLAGS) -c $< -o $@
	@echo "Compiled $@"

# depends on object files only
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Main functions added to $(NAME)"

# depends on object files only
bonus: $(OBJ) $(OBJ_BONUS) $(H)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	@echo "Bonus functions added to $(NAME)"

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "Libft's object files cleaned"

fclean:	clean
	@rm -f $(NAME) libft.so
	@echo "$(NAME) cleaned"

re: fclean all

# compiles main.c for testing and delete binary after test run
# test: $(NAME)
# 	$(COMPILER) main.c $(NAME) -lbsd -g
# 	ldd a.out
# 	@echo "Compiled main.c -> a.out"
# 	./a.out
#	@rm -f a.out

# for 'libft-unit-tests' on linux
# so:
# 	gcc -g -fPIC -Wall -Werror -Wextra ft*.c -shared -o libft.so

.PHONY: clean fclean all re bonus
