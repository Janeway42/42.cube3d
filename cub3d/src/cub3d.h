#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "MLX42/MLX42.h"
# include "cub3d_struct.h"
# include "colours.h"
# include "libft.h"


//testing REMOVE
# include <stdio.h>

//----------------------------------------
// Cub3d utility functions
//----------------------------------------

t_coor			vec_to_coor(t_vector vec);
t_vector		add_vectors(t_vector vec1, t_vector vec2);
t_vector		subtract_vectors(t_vector vec1, t_vector vec2);
t_vector		rotate_vector(t_vector vect, double degree);
unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b,
					unsigned char a);

//----------------------------------------
// Bresenham line draw algorithm
//----------------------------------------

void			draw_line(t_coor point1, t_coor point2, mlx_image_t *img,
					unsigned int colour);
void			draw_line_low_slope(t_coor point1, t_coor point2,
					mlx_image_t *img, unsigned int colour);
void			draw_line_high_slope(t_coor point1, t_coor point2,
					mlx_image_t *img, unsigned int colour);
long			abs_int(int number);

//----------------------------------------
// Digital differential Analyzer (DDA)
//----------------------------------------

//	calculate the distance to the first wall it hits

t_dda			apply_dda(t_vector playerpos, t_vector ray, double angle,
					char **map);
double			calc_distance_to_wall(t_vector playerpos, t_vector ray,
					char **map);

//----------------------------------------
// Image buffer functions
//----------------------------------------
void			draw_pixel(mlx_image_t *img, unsigned int x, unsigned int y,
					unsigned int colour);
void			clear_image(mlx_image_t *img);

//----------------------------------------
// Map2d functions (2d minimap)
//----------------------------------------
int				init_minimap(t_data *gamedata);
void			draw_player(mlx_image_t *img, t_player player,
					unsigned int pixelsize);
void			draw_map(t_data *data);
void			draw_wall(mlx_image_t *img, int x, int y,
					unsigned int pixelsize);
void			draw_floor(mlx_image_t *img, int x, int y,
					unsigned int pixelsize);
void			draw_ray(mlx_image_t *img, t_vector ray, t_vector playerpos,
					unsigned int pixelsize);
t_vector		calc_ray_vector(double degree, double distance);
void			draw_viewing_cone(t_data *data);

//----------------------------------------
// Projection 3d functions 
//----------------------------------------

void			create_projection(t_data *data);
void			draw_wall_col(t_data *data, unsigned int x,
					unsigned int wall_height);
void			draw_floor_ceiling(t_data *data, unsigned int top,
					unsigned int bottom, unsigned int x);
// void			draw_wall(t_data *data, unsigned int x, unsigned int wall_height);
// unsigned int	get_colour_png(mlx_texture_t *png, unsigned int x, unsigned int y);
#endif