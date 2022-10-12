NAME = cube3D
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address

S_SRC	=	main.c

S_PATH	=	src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

UTILS		=	error_free_exit.c\
				utils.c
UTILS_PATH	=	utils/
UTILS_OBJ	=	$(UTILS:%.c=$(UTILS_PATH)%.o)

GNL			=	get_next_line.c\
				get_next_line_utils.c
GNL_PATH	=	get_next_line/
GNL_OBJ		=	$(GNL:%.c=$(GNL_PATH)%.o)

OBJ_FILES = $(S_OBJ) $(UTILS_OBJ) $(GNL_OBJ)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C libft
	make -C mlx
	mv mlx/libmlx.dylib .
	$(CC) $(CFLAGS) $(OBJ_FILES) -L. -lmlx -framework OpenGL -framework AppKit libft/libft.a -o $(NAME)
	
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	make clean -C mlx
	$(RM) $(OBJ_FILES)

fclean: clean
	make fclean -C libft
	make clean -C mlx
	$(RM) libmlx.dylib
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re