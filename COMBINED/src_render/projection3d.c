#include "../includes/render.h"

void	draw_wall_col(t_info *data, unsigned int x, unsigned int wall_height)
{
	unsigned int	top;
	unsigned int	bottom;
	t_coor			walltop;
	t_coor			wallbottom;
	unsigned char	gradiant;

	if (wall_height > data->img->height)
		wall_height = data->img->height;
	top = (data->img->height / 2 - wall_height / 2);
	bottom = top + wall_height;
	walltop.x = x;
	walltop.y = top;
	wallbottom.x = x;
	wallbottom.y = bottom;
	gradiant = (unsigned char)(255 * (wall_height / (double)data->img->height));
	draw_line(walltop, wallbottom, data->img,
		create_colour(gradiant, 0, 0, 255));
	draw_floor_ceiling(data, top, bottom, x);
}

void	draw_floor_ceiling(t_info *data, unsigned int top, unsigned int bottom,
			unsigned int x)
{
	t_coor	ceilingtop;
	t_coor	ceilingbottom;
	t_coor	floortop;
	t_coor	floorbottom;

	ceilingtop.x = x;
	ceilingtop.y = 0;
	ceilingbottom.x = x;
	ceilingbottom.y = top - 1;
	floortop.x = x;
	floortop.y = bottom + 1;
	floorbottom.x = x;
	floorbottom.y = (int)(data->img->height - 1);
	draw_line(ceilingtop, ceilingbottom, data->img, data->ceiling_colour);
	draw_line(floortop, floorbottom, data->img, data->floor_colour);
}

void	create_projection(t_info *data)
{
	unsigned int	i;
	double			angle;
	double			ps;
	unsigned int	wall_height;
	t_dda			dda_result;

	i = 0;
	while (i < data->img->width)
	{
		ps = tanf(((data->player.fov / 2.0) / 180) * M_PI);
		angle = (atanf(-ps + ((2.0 * ps * i) / data->img->width)) * 180)
			/ M_PI;
		dda_result = apply_dda(data->player.position,
				rotate_vector(data->player.heading_vector,
					data->player.heading_degree - angle), angle, data->map);
		wall_height = (unsigned int)(data->img->height / dda_result.perp_dist);
// if (angle == 0)
// 	printf("side : %d, distance %f hitpos %f\n", dda_result.side, dda_result.distance, dda_result.hitpos);
		draw_wall_col(data, i, wall_height);
		++i;
	}
}

// void	draw_wall(t_info *data, unsigned int x, unsigned int wall_height, double wallX)
// {	
// 	unsigned int	top;
// 	unsigned int	bottom;
// 	double			step;

// 	int draw_start = -wall_height /2 + data->img->height /2;
// 	if(draw_start < 0) 
// 		draw_start = 0;
// 	int draw_end = wall_height /2 + data->img->height /2;
// 	if (draw_end >= data->img->height)
// 		draw_end = data->img->height - 1;
// 	step = data->img->height / wall_height;
// 	int texX = (int)(wallX * (double)(data->img->height));
// 	if (wall_height <= data->img->height)
// 	{
		
// 	}
// 	else
// 	{

// 	}

// }

// unsigned int get_colour_png(mlx_texture_t* png, unsigned int x, unsigned y)
// {
// 	unsigned int offset;
// 	unsigned char	*dst;

// 	if(x < png->width && y < png->height)
// 	{
// 		offset = y * (png->width * 4) + x * 4;
// 		dst = png->pixels + offset;
// 		return (*(unsigned int*) dst);
// 	}
// 	return (0X00000000);
// }