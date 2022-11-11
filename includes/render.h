#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include "render_struct.h"
# include "colours.h"
# include "libft.h"
# include "initialize.h"

//definition windows resolution
#define WIDTH 1280
#define HEIGHT 720
#define MINIMAP_MAX_PIXEL_SIZE 400

//testing REMOVE
# include <stdio.h>

//----------------------------------------
// render init functions
//----------------------------------------

int				init_gamestate(t_data *data, t_info *gamedata, mlx_t *mlx);

//----------------------------------------
// vector functions
//----------------------------------------

t_coor			vec_to_coor(t_vector vec);
t_vector		add_vectors(t_vector vec1, t_vector vec2);
t_vector		subtract_vectors(t_vector vec1, t_vector vec2);
t_vector		rotate_vector(t_vector vect, double degree);

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

t_dda			apply_dda(t_vector playerpos, t_vector ray, double angle,
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
int				init_minimap(t_info *gamedata, unsigned int max_pixels_minimap);
void			draw_player(mlx_image_t *img, t_player player,
					unsigned int pixelsize);
void			draw_map(t_info *data);
void			draw_ray(mlx_image_t *img, t_vector ray, t_vector playerpos,
					unsigned int pixelsize);
t_vector		calc_ray_vector(double degree, double distance);
void			draw_viewing_cone(t_info *data);

//----------------------------------------
// Projection 3d functions 
//----------------------------------------
void			create_projection(t_info *data);

//----------------------------------------
// Colour functions
//----------------------------------------
unsigned int	get_colour_png(mlx_texture_t *png, unsigned int x, unsigned int y);
unsigned char	get_colour_value(unsigned int colour, char colourpart);
unsigned int	grading_colour(unsigned int colour, double percentage);
unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b,
					unsigned char a);
#endif