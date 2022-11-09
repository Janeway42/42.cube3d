#include "../includes/render.h"

// with the degree of the angle and the length of the hypotenuse
// the vector is being calculated and returned 
t_vector	calc_ray_vector(double degree, double distance)
{
	t_vector	ray;
	double		radians;

	radians = (degree / 180.0) * M_PI;
	ray.x = cos(radians) * distance;
	ray.y = sin(radians) * distance;
	return (ray);
}

void	draw_viewing_cone(t_info *data)
{
	double		i;
	t_dda		result;
	t_vector	current_heading;
	t_vector	ray;

	i = (-1 * (data->player.fov / 2.0));
	while (i < (data->player.fov / 2.0))
	{
		current_heading = rotate_vector(data->player.vector,
				data->player.degree + i);
		result = apply_dda(data->player.position, current_heading, i,
				data->map);
		ray = calc_ray_vector(data->player.degree + i,
				result.distance);
		draw_ray(data->imgmini, ray, data->player.position,
			data->mini_pixelsize);
		i += .25;
	}
}

void	draw_ray(mlx_image_t *img, t_vector ray, t_vector playerpos,
			unsigned int pixelsize)
{
	t_coor	start;
	t_coor	end;

	start.x = playerpos.x * pixelsize;
	start.y = playerpos.y * pixelsize;
	end.x = start.x + ray.x * pixelsize;
	end.y = start.y - ray.y * pixelsize;
	draw_line(start, end, img, RED);
}
