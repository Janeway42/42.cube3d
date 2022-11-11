#include "../includes/render.h"

static void	process_movement_input(t_info *data, double angle)
{
	t_vector	mov_vector;
	t_dda		result;

	mov_vector = rotate_vector(data->player.vector,
			data->player.degree + angle);
	result = apply_dda(data->player.position, mov_vector,
			data->player.degree + angle, data->map);
	if (result.distance > 0.1)
	{
		data->player.position.x += mov_vector.x * 0.01 * data->player.speed;
		data->player.position.y += mov_vector.y * 0.01 * data->player.speed;
	}
}

static void	process_input_key(t_info *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.degree = fmod(data->player.degree
				- data->rotation_angle + 360, 360);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.degree = fmod(data->player.degree
				+ data->rotation_angle, 360);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		process_movement_input(data, 0.0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		process_movement_input(data, 270.0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		process_movement_input(data, 90.0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		process_movement_input(data, 180.0);
}

void	hook(void *param)
{
	t_info		*data;

	data = (t_info *) param;
	process_input_key(data);
	clear_image(data->img);
	create_projection(data);
	clear_image(data->imgmini);
	draw_map(data);
	draw_viewing_cone(data);
	draw_player(data->imgmini, data->player, data->mini_pixelsize);
}

void	render(t_data *data)
{
	mlx_t			*mlx;
	t_info			gamedata;
	unsigned int	max_pixels_minimap;

	max_pixels_minimap = MINIMAP_MAX_PIXEL_SIZE;
	mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!mlx)
		error_exit_input("Couldn't initialize MLX\n");
	if (init_gamestate(data, &gamedata, mlx) == -1)
		error_exit_input("Something went wrong with initializing gamestate\n");
	create_projection(&gamedata);
	if (init_minimap(&gamedata, max_pixels_minimap) == -1)
		error_exit_input("Something went wrong with initializing minimap\n");
	draw_map(&gamedata);
	draw_viewing_cone(&gamedata);
	draw_player(gamedata.imgmini, gamedata.player, gamedata.mini_pixelsize);
	mlx_image_to_window(gamedata.mlx, gamedata.img, 0, 0);
	mlx_image_to_window(gamedata.mlx, gamedata.imgmini,
		gamedata.img->width - gamedata.imgmini->width,
		gamedata.img->height - gamedata.imgmini->height);
	mlx_loop_hook(gamedata.mlx, &hook, &gamedata);
	mlx_loop(gamedata.mlx);
	mlx_delete_texture(gamedata.texture[0]);
	mlx_delete_texture(gamedata.texture[1]);
	mlx_delete_texture(gamedata.texture[2]);
	mlx_delete_texture(gamedata.texture[3]);
	mlx_delete_image(gamedata.mlx, gamedata.img);
	mlx_delete_image(gamedata.mlx, gamedata.imgmini);
	mlx_terminate(gamedata.mlx);
}
