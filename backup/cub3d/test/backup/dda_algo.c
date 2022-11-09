#include "cub3d.h"

double	ft_absf(double number)
{
	if (number < 0)
		return (-1 * number);
	return (number);
}

void	init_dda(t_dda_vars *vars, t_dda *result, t_vector *pos, t_vector *ray)
{
	if (ray->x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (pos->x - vars->map_x) * vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - pos->x) * vars->delta_dist_x;
	}
	if (ray->y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (pos->y - vars->map_y) * vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - pos->y) * vars->delta_dist_y;
	}
}

//function that will start the dda algorithm
//side 0 is east side of a square
//side 1 is south side of a square
//side 2 is west side of a square
//side 3 is north side of a square

void	start_dda(t_dda_vars *vars, t_dda *result, double angle, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			result->side = 0 + (vars->step_x + 1);
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			result->side = 1 + (vars->step_y + 1);
		}
		if (map[vars->map_y][vars->map_x] == '1')
			hit = 1;
	}
	if (result->side == 0 || result->side == 2)
		result->distance = (vars->side_dist_x - vars->delta_dist_x);
	else
		result->distance = (vars->side_dist_y - vars->delta_dist_y);
	result->perp_dist = cos((angle / 180) * M_PI) * result->distance;
}

t_dda	apply_dda(t_vector playerpos, t_vector ray, double angle, char **map)
{
	t_dda		result;
	t_dda_vars	dda_vars;

	dda_vars.map_x = (int) playerpos.x;
	dda_vars.map_y = (int) playerpos.y;
	dda_vars.delta_dist_x = ft_absf(1 / ray.x);
	dda_vars.delta_dist_y = ft_absf(1 / ray.y);
	init_dda(&dda_vars, &result, &playerpos, &ray);
	start_dda(&dda_vars, &result, angle, map);
	if (result.side == 0 || result.side == 2)
		result.hitpos = playerpos.y + result.perp_dist * ray.y;
	else
		result.hitpos = playerpos.x + result.perp_dist * ray.x;
	result.hitpos -= floorf(result.hitpos);
	return (result);
}

//backup old version
// double calc_distance_to_wall(t_vector playerpos, t_vector ray,  char **map)
// {
// 	double rayDirX = ray.x;
// 	double rayDirY = ray.y; 

// 	int mapX = (int) playerpos.x;
// 	int mapY = (int) playerpos.y;

// 	double sideDistX;
// 	double sideDistY;

// 	double deltaDistX = ft_absf(1 / rayDirX);
// 	double deltaDistY = ft_absf(1 / rayDirY);
	
// 	int stepX;
// 	int stepY;

// 	int hit = 0;
// 	int side;

// 	double distance;

// 	if (rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (playerpos.x - mapX) * deltaDistX;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = (mapX + 1.0 - playerpos.x) * deltaDistX;
// 	}
// 	if (rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (playerpos.y - mapY) * deltaDistY;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = (mapY + 1.0 - playerpos.y) * deltaDistY;
// 	}
// 	while (hit == 0)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			mapY += stepY;
// 			side = 1;
// 		}
// 		if (map[mapY][mapX] == '1')
// 			hit = 1;
// 	}
	
// 	if (side == 0)
// 		distance = (sideDistX - deltaDistX);
// 	else
// 		distance = (sideDistY - deltaDistY);
// 	return (distance);
// }