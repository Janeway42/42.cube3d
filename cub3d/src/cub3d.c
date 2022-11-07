#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "cub3d_struct.h"
#include "cub3d.h"
#include "colours.h"

//definition windows resolution
#define WIDTH 1000
#define HEIGHT 1000


//test
#define MINIMAPMAX 400 
#include "testmap.h"

void	hook(void *param)
{
	t_data		*data;
	t_vector	movement_vector;
	t_dda		result;

	data = (t_data *) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		movement_vector = rotate_vector(data->player.heading_vector, data->player.heading_degree);
		result = apply_dda(data->player.position, movement_vector, data->player.heading_degree, data->map);
		if (result.distance > 0.1)
		{
			data->player.position.x += movement_vector.x * 0.01 * data->player.speed;
			data->player.position.y += movement_vector.y * 0.01 * data->player.speed;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		movement_vector = rotate_vector(data->player.heading_vector, data->player.heading_degree + 180.0);
		result = apply_dda(data->player.position, movement_vector, data->player.heading_degree + 180.0, data->map);
		if (result.distance > 0.1)
		{
			data->player.position.x += movement_vector.x * 0.01 * data->player.speed;
			data->player.position.y += movement_vector.y * 0.01 * data->player.speed;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player.heading_degree = fmod(data->player.heading_degree - data->rotation_angle + 360, 360);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player.heading_degree = fmod(data->player.heading_degree + data->rotation_angle, 360);
	}
	clear_image(data->img);
	create_projection(data);
	clear_image(data->imgmini);
	draw_map(data);
	draw_viewing_cone(data);
	draw_player(data->imgmini, data->player, data->mini_pixelsize);
}

int	init_gamestate(t_data *gamedata, mlx_t *mlx)
{
	gamedata->mlx = mlx;
	gamedata->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!gamedata->img)
		return (-1);
	gamedata->player.position.x = 2.5;
	gamedata->player.position.y = 2.5;
	gamedata->player.heading_degree = 270.0;
	gamedata->player.heading_vector.x = 1.0;
	gamedata->player.heading_vector.y = 0.0;
	gamedata->player.speed = 5;
	gamedata->player.fov = 90;
	gamedata->rotation_angle = 3.0;
	gamedata->map = create_map();
	if (gamedata->map == NULL)
		return (-1);
	gamedata->map_width = mapwidth;
	gamedata->map_height = mapheight;
	gamedata->ceiling_colour = LIGHTSKYBLUE;
	gamedata->floor_colour = GREEN;
	return (1);
}

int	main(int argc, char *argv[])
{
	mlx_t	*mlx;
	t_data	gamedata;	

	(void) argc;
	(void) argv;
	mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);//create the window and set resize to true
	if (!mlx) //exit if failure to initialize mlx instance
		exit(EXIT_FAILURE);

	//load texture
	gamedata.texture = mlx_load_png("brick.png");
	//start projection
	if (init_gamestate(&gamedata, mlx) == -1)
		exit(EXIT_FAILURE);
	create_projection(&gamedata);
	//start minimap
	if (init_minimap(&gamedata) == -1)
		exit(EXIT_FAILURE);
	draw_map(&gamedata);
	draw_viewing_cone(&gamedata);
	draw_player(gamedata.imgmini, gamedata.player, gamedata.mini_pixelsize);
	//push images to window
	mlx_image_to_window(gamedata.mlx, gamedata.img, 0, 0); //pushing buffer to window starting coordinates 0, 0
	mlx_image_to_window(gamedata.mlx, gamedata.imgmini, gamedata.img->width - gamedata.imgmini->width, gamedata.img->height - gamedata.imgmini->height); //the order in which each imagebuffer is drawn to the window is important. 
	//the buffers will be refresh in order you draw to the window. 
	mlx_loop_hook(gamedata.mlx, &hook, &gamedata);
	mlx_loop(gamedata.mlx);
	mlx_terminate(gamedata.mlx);
	return (EXIT_SUCCESS);
}