NAME = cube3D
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address

S_SRC	=	main.c\
			process_input.c\
			process_path_color.c\
			process_map.c


S_PATH	=	src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

UTILS		=	error.c\
				free.c
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
	$(CC) $(CFLAGS) $(OBJ_FILES) libft/libft.a -o $(NAME)
	
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	$(RM) $(OBJ_FILES)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re