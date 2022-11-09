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
	unsigned int	x;
	double			angle;
	double			ps;
	unsigned int	wall_height;
	t_dda			dda_result;

	x = 0;
	while (x < data->img->width)
	{
		ps = tanf(((data->player.fov / 2.0) / 180) * M_PI);
		angle = (atanf(-ps + ((2.0 * ps * x) / data->img->width)) * 180)
			/ M_PI;
		dda_result = apply_dda(data->player.position,
				rotate_vector(data->player.heading_vector,
					data->player.heading_degree - angle), angle, data->map);
		wall_height = (unsigned int)(data->img->height / dda_result.perp_dist);
		draw_tex_wall(data, x, wall_height, &dda_result);
		++x;
	}
}

void	draw_tex_wall(t_info *data, unsigned int x, unsigned int wall_height, t_dda *result)
{	
	unsigned int	top;
	unsigned int	bottom;
	double			step;
	unsigned int 	height;
	double	tex_start;
	unsigned int	colour;
	mlx_texture_t *texture;

	if(result->side == 0 || result->side == 2)
		texture = data->texture2;
	else
		texture = data->texture1;
	height = data->img->height;
	if (wall_height > height)
	{
		top = 0;
		bottom = height - 1;
		tex_start = (((1 -(1.0* height/ wall_height)) / 2.0) * texture->height);
	}
	else
	{
		top = (height - wall_height) / 2;
		bottom = (height + wall_height) / 2;
		tex_start = 0.0;
	}
	step = 1.0 * texture->height / wall_height;
	for(unsigned int y = 0; y <= bottom - top; y++)
	{
		
		if (result->side == 0 || result->side == 3)
			colour = get_colour_png(texture, (unsigned int) ((1.0- result->hitpos) * texture->width), (unsigned int) (tex_start + y * step));
		else
			colour = get_colour_png(texture, (unsigned int) (result->hitpos * texture->width), (unsigned int) (tex_start + y * step));
		colour = grading_colour(colour, 1.0 * wall_height / height);
		draw_pixel(data->img, x, y + top, colour);
	}
	draw_floor_ceiling(data, top, bottom, x);
}

unsigned int grading_colour(unsigned int colour, double percentage)
{
	unsigned char R;
	unsigned char G;
	unsigned char B;

	if(percentage < 1.0)
	{
		R = (unsigned char) (percentage * get_colour_value(colour,'R'));
		G = (unsigned char) (percentage * get_colour_value(colour,'G'));
		B = (unsigned char) (percentage * get_colour_value(colour,'B'));
		return (create_colour(R,G,B,255));
	}
	return (colour);
}


unsigned int get_colour_png(mlx_texture_t* png, unsigned int x, unsigned y)
{
	unsigned int offset;
	unsigned char	*dst;

	if(x < png->width && y < png->height)
	{
		offset = y * (png->width * 4) + x * 4;
		dst = png->pixels + offset;
		return (*(unsigned int*) dst);
	}
	return (0XFF000000);
}

unsigned char get_colour_value(unsigned int colour,char colourpart)
{
	if(colourpart == 'R')
		return ((unsigned char)(colour & 0x000000FF));
	else if (colourpart == 'G')
		return ((unsigned char)((colour & 0x0000FF00)>>8));
	else if (colourpart == 'B')
		return ((unsigned char)((colour & 0x00FF0000)>>16));
	return (0);
}
