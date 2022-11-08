#include "cub3d.h"

int	init_minimap(t_data *gamedata)
{
	unsigned int	miniwidth;
	unsigned int	miniheight;
	unsigned int	max_pixels;

	max_pixels = 250;
	if (gamedata->map_width > gamedata->map_height)
	{
		gamedata->mini_pixelsize = max_pixels
			/ gamedata->map_width;
		miniwidth = gamedata->mini_pixelsize * gamedata->map_width;
		miniheight = gamedata->mini_pixelsize * gamedata->map_height;
	}
	else
	{
		gamedata->mini_pixelsize = max_pixels
			/ gamedata->map_height;
		miniheight = gamedata->mini_pixelsize * gamedata->map_height;
		miniwidth = gamedata->mini_pixelsize * gamedata->map_width;
	}
	gamedata->imgmini = mlx_new_image(gamedata->mlx, miniwidth, miniheight);
	if (gamedata->imgmini == NULL)
		return (-1);
	return (1);
}

void	draw_player(mlx_image_t *img, t_player player, unsigned int pixelsize)
{
	unsigned int	x;
	unsigned int	y;
	t_vector		playerpos;
	t_vector		headingline;

	y = 0;
	playerpos.x = player.position.x * pixelsize;
	playerpos.y = player.position.y * pixelsize;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			draw_pixel(img, playerpos.x - 1 + x, playerpos.y - 1 + y, WHITE);
			++x;
		}
		++y;
	}
	headingline = rotate_vector(player.heading_vector, player.heading_degree);
	headingline.x *= 10;
	headingline.y *= 10;
	draw_line(vec_to_coor(playerpos), vec_to_coor(add_vectors(playerpos,
				headingline)), img, WHITE);
}

void	draw_map(t_data *data)
{
	unsigned int	pixelsize;
	int				y;
	int				x;

	pixelsize = (unsigned int)(data->imgmini->width / data->map_width);
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				draw_wall(data->imgmini, x * pixelsize, y * pixelsize,
					pixelsize);
			else if (data->map[y][x] == '0' || data->map[y][x] == ' ')
				draw_floor(data->imgmini, x * pixelsize, y * pixelsize,
					pixelsize);
			++x;
		}
		++y;
	}
}

void	draw_wall(mlx_image_t *img, int x, int y, unsigned int pixelsize)
{
	int	wall_x;
	int	wall_y;

	wall_x = x;
	wall_y = y;
	while (wall_x < x + pixelsize - 1)
	{
		wall_y = y;
		while (wall_y < y + pixelsize - 1)
		{
			draw_pixel(img, wall_x, wall_y, WHITE);
			++wall_y;
		}
		++wall_x;
	}
}

void	draw_floor(mlx_image_t *img, int x, int y, unsigned int pixelsize)
{
	int	floor_x;
	int	floor_y;

	floor_x = x;
	floor_y = y;
	while (floor_x < x + pixelsize)
	{
		floor_y = y;
		while (floor_y < y + pixelsize)
		{
			draw_pixel(img, floor_x, floor_y, GREY);
			++floor_y;
		}
		++floor_x;
	}
}
