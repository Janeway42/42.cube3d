NAME = cub3d
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address
UNAME = $(shell uname -s)

# libraries
LIB_DIR = lib
LIB_FLAGS = $(LIBFT_FLAGS) $(MLX42_FLAGS) 
LIB_INCLUDE = $(LIBFT_INCLUDE) $(MLX42_INCLUDE)

#libft library
LIBFT_DIR = libft
LIBFT_FLAGS = -L$(LIB_DIR)/$(LIBFT_DIR) -lft
LIBFT_INCLUDE = -I$(LIB_DIR)/$(LIBFT_DIR)

#MLX42 library
MLX42_DIR = MLX42
MLX42_INCLUDE = -I$(LIB_DIR)/$(MLX42_DIR)/include
ifeq ($(UNAME), Darwin)
	MLX42_FLAGS = -L$(LIB_DIR)/$(MLX42_DIR) -lmlx42 -L$(shell brew --prefix glfw)/lib -lglfw
endif
ifeq ($(UNAME), Linux)
	MLX42_FLAGS = -I$(LIB_DIR)/$(MLX42_DIR)/include -L./$(LIB_DIR)/$(MLX42_DIR) -lmlx42 -ldl -lglfw -pthread -lm
endif

#source code
SRC_INIT_DIR	=	src_init/
SRC_INIT	=	main.c\
				process_input.c\
				process_input_utils.c\
				process_path_color.c\
				process_map.c\
				process_map_validity.c

SRC_RENDER_DIR = src_render/
SRC_RENDER = 	render.c\
				render_init.c \
				vector_functions.c \
				bres_algo.c \
				image_buffer_functions.c\
				map2d_functions.c \
				map2d_functions_utils.c \
				dda_algo.c \
				projection3d.c \
				colour_functions.c

UTILS_DIR	=	utils/
UTILS		=	error.c\
				free.c

GNL_DIR	=	get_next_line/
GNL			=	get_next_line.c\
				get_next_line_utils.c

#object files
OBJ_INIT		=	$(SRC_INIT:%.c=$(SRC_INIT_DIR)%.o)
OBJ_RENDER		=	$(SRC_RENDER:%.c=$(SRC_RENDER_DIR)%.o)
OBJ_UTILS		=	$(UTILS:%.c=$(UTILS_DIR)%.o)
OBJ_GNL		=	$(GNL:%.c=$(GNL_DIR)%.o)

OBJ_FILES = $(OBJ_INIT) $(OBJ_RENDER) $(OBJ_UTILS) $(OBJ_GNL)

#makeflie
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR) 
	$(MAKE) -C $(LIB_DIR)/$(MLX42_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIB_INCLUDE) $(LIB_FLAGS) -O3

%.o: %.c $(HEADER_FILES)
	@mkdir -p obj
	$(CC) $(CFLAGS) $(LIB_INCLUDE) -c $< -o $@ 

clean:
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR) clean
	$(MAKE) -C $(LIB_DIR)/$(MLX42_DIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR) fclean
	$(MAKE) -C $(LIB_DIR)/$(MLX42_DIR) fclean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
