#!/bin/bash

gcc $1 -I../lib/MLX42/include -L../lib/MLX42 -lmlx42 -L$(brew --prefix glfw)/lib -lglfw