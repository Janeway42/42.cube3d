CC = gcc
CFLAGS = -g #-Wall -Wextra -Werror  

NAME = cub3d
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
SRC_DIR = src
SRC_FILES = $(addprefix $(SRC_DIR)/,\
				cub3d.c\
				cub3d_utils.c \
				bres_algo.c \
				image_buffer_functions.c\
				map2d_functions.c \
				map2d_functions_utils.c \
				dda_algo.c \
				projection3d.c \
				testmap.c)

#object files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR) 
	$(MAKE) -C $(LIB_DIR)/$(MLX42_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIB_INCLUDE) $(LIB_FLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
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