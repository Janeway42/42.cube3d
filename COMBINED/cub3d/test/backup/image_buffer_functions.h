#ifndef IMAGE_BUFFER_FUNCTIONS_H
# define IMAGE_BUFFER_FUNCTIONS_H

# include "MLX42/MLX42.h"

void			draw_pixel(mlx_image_t *img, unsigned int x, unsigned int y,
					unsigned int colour);
void			clear_image(mlx_image_t *img);

#endif