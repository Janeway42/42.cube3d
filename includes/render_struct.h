#ifndef RENDER_STRUCT_H
# define RENDER_STRUCT_H

# include "MLX42/MLX42.h"

typedef struct s_coor
{
	int	x;
	int	y;
}				t_coor;

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_player
{
	t_vector		position;
	t_vector		heading_vector;
	double			heading_degree;
	unsigned int	speed;
	unsigned int	fov;
}				t_player;

typedef struct s_info
{
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture[4];
	char			**map;
	double			rotation_angle;
	unsigned int	floor_colour;
	unsigned int	ceiling_colour;
	unsigned int	map_width;
	unsigned int	map_height;
	unsigned int	mini_pixelsize;
	mlx_image_t		*imgmini;
}				t_info;

typedef struct s_dda
{
	int			side;
	double		hitpos;
	double		distance;
	double		perp_dist;
}				t_dda;

typedef struct s_dda_vars
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;

}			t_dda_vars;

#endif
