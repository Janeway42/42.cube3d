#include "../includes/render.h"

static void	process_input_key(t_info *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.degree = fmod(data->player.degree
				- data->rotation_angle + 360, 360);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.degree = fmod(data->player.degree
				+ data->rotation_angle, 360);
}

static void	process_input_key2(t_info *data)
{	
	t_vector	mov_vector;
	t_dda		result;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		mov_vector = rotate_vector(data->player.vector, data->player.degree);
		result = apply_dda(data->player.position, mov_vector,
				data->player.degree, data->map);
		if (result.distance < 0.1)
			return ;
		data->player.position.x += mov_vector.x * 0.01 * data->player.speed;
		data->player.position.y += mov_vector.y * 0.01 * data->player.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		mov_vector = rotate_vector(data->player.vector,
				data->player.degree + 180.0);
		result = apply_dda(data->player.position, mov_vector,
				data->player.degree + 180.0, data->map);
		if (result.distance > 0.1)
		{
			data->player.position.x += mov_vector.x * 0.01 * data->player.speed;
			data->player.position.y += mov_vector.y * 0.01 * data->player.speed;
		}
	}
}

void	hook(void *param)
{
	t_info		*data;

	data = (t_info *) param;
	process_input_key(data);
	process_input_key2(data);
	clear_image(data->img);
	create_projection(data);
	clear_image(data->imgmini);
	draw_map(data);
	draw_viewing_cone(data);
	draw_player(data->imgmini, data->player, data->mini_pixelsize);
}

static int	init_gamestate(t_data *data, t_info *gamedata, mlx_t *mlx)
{
	gamedata->mlx = mlx;
	gamedata->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!gamedata->img)
		return (-1);
	gamedata->player.position.x = data->player_pos[1];
	gamedata->player.position.y = data->player_pos[0];
	gamedata->player.degree = data->player_direction;
	gamedata->player.vector.x = 1.0;
	gamedata->player.vector.y = 0.0;
	gamedata->player.speed = 5;
	gamedata->player.fov = 90;
	gamedata->rotation_angle = 3.0;
	gamedata->map = data->map;
	if (gamedata->map == NULL)
		return (-1);
	gamedata->map_width = data->map_columns;
	gamedata->map_height = data->map_rows;
	gamedata->texture[0] = mlx_load_png(data->east);
	gamedata->texture[1] = mlx_load_png(data->south);
	gamedata->texture[2] = mlx_load_png(data->west);
	gamedata->texture[3] = mlx_load_png(data->north);
	gamedata->ceiling_colour = create_colour((unsigned char)data->ceiling[0], (unsigned char)data->ceiling[1], (unsigned char)data->ceiling[2], 255);
	gamedata->floor_colour = create_colour((unsigned char)data->floor[0], (unsigned char)data->floor[1], (unsigned char)data->floor[2], 255);
	return (1);
}

void	render(t_data *data)
{
	mlx_t	*mlx;
	t_info	gamedata;

	mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	if (init_gamestate(data, &gamedata, mlx) == -1)
		exit(EXIT_FAILURE);
	create_projection(&gamedata);
	if (init_minimap(&gamedata) == -1)
		exit(EXIT_FAILURE);
	draw_map(&gamedata);
	draw_viewing_cone(&gamedata);
	draw_player(gamedata.imgmini, gamedata.player, gamedata.mini_pixelsize);
	mlx_image_to_window(gamedata.mlx, gamedata.img, 0, 0);
	mlx_image_to_window(gamedata.mlx, gamedata.imgmini, gamedata.img->width - gamedata.imgmini->width, gamedata.img->height - gamedata.imgmini->height);
	mlx_loop_hook(gamedata.mlx, &hook, &gamedata);
	mlx_loop(gamedata.mlx);
	mlx_terminate(gamedata.mlx);
}
