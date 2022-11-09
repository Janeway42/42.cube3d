#ifndef MAP2D_FUNCTIONS_H
# define MAP2D_FUNCTIONS_H

# include "MLX42/MLX42.h"
# include "cub3d_struct.h"

void        draw_player(mlx_image_t *img, t_player player, unsigned int pixelsize);
void	    draw_map(t_data *data);
void	    draw_wall(mlx_image_t *img, int x, int y, unsigned int pixelsize);
void	    draw_floor(mlx_image_t *img, int x, int y, unsigned int pixelsize);
void        draw_ray(mlx_image_t *img, t_vector ray, t_vector playerpos, unsigned int pixelsize);
t_vector    calc_ray_vector(double degree, double distance);

#endif