#include "../includes/render.h"

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
				rotate_vector(data->player.vector,
					data->player.degree - angle), angle, data->map);
		wall_height = (unsigned int)(data->img->height / dda_result.perp_dist);
		draw_tex_wall(data, x, wall_height, &dda_result);
		++x;
	}
}

void	draw_tex_wall(t_info *data, unsigned int x, unsigned int wall_height
			, t_dda *result)
{	
	t_draw_tex_vars	vars;

	vars.wall = data->texture[result->side];
	if (wall_height > data->img->height)
	{
		vars.top = 0;
		vars.bottom = data->img->height - 1;
		vars.tex_start = (((1 - (1.0 * data->img->height / wall_height)) / 2.0)
				* vars.wall->height);
	}
	else
	{
		vars.top = (data->img->height - wall_height) / 2;
		vars.bottom = (data->img->height + wall_height) / 2;
		vars.tex_start = 0.0;
	}
	vars.step = 1.0 * vars.wall->height / wall_height;
	vars.wall_height_perc = 1.0 * wall_height / data->img->height;
	draw_tex_wall_column(data->img, x, result, &vars);
	draw_floor_ceiling(data, vars.top, vars.bottom, x);
}

void	draw_tex_wall_column(mlx_image_t *img, unsigned int x, t_dda *result
			, t_draw_tex_vars *vars)
{
	unsigned int	y;
	unsigned int	colour;

	y = 0;
	while (y <= vars->bottom - vars->top)
	{
		if (result->side == EAST || result->side == NORTH)
			colour = get_colour_png(vars->wall,
					(unsigned int)((1.0 - result->hitpos) * vars->wall->width),
					(unsigned int)(vars->tex_start + y * vars->step));
		else
				colour = get_colour_png(vars->wall,
					(unsigned int)(result->hitpos * vars->wall->width),
					(unsigned int)(vars->tex_start + y * vars->step));
		colour = grading_colour(colour, vars->wall_height_perc);
		draw_pixel(img, x, y + vars->top, colour);
		++y;
	}
}
