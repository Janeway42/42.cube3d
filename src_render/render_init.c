/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:07:57 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/16 12:46:29 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

//load the textures
static void	load_textures(t_data *data, t_info *gamedata)
{
	int	i;

	gamedata->texture[0] = mlx_load_png(data->east);
	gamedata->texture[1] = mlx_load_png(data->south);
	gamedata->texture[2] = mlx_load_png(data->west);
	gamedata->texture[3] = mlx_load_png(data->north);
	free(data->west);
	free(data->north);
	free(data->south);
	free(data->east);
	i = 0;
	while (i < 4)
	{
		if (gamedata->texture[i] == NULL)
			error_exit_input("Texture could not be loaded.");
		++i;
	}
}

//initialize the gamestate
int	init_gamestate(t_data *data, t_info *gamedata, mlx_t *mlx)
{
	gamedata->mlx = mlx;
	gamedata->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!gamedata->img)
		return (FAILURE);
	load_textures(data, gamedata);
	gamedata->player.position.x = data->player_pos[1];
	gamedata->player.position.y = data->player_pos[0];
	gamedata->player.degree = data->player_direction;
	gamedata->player.vector.x = 1.0;
	gamedata->player.vector.y = 0.0;
	gamedata->player.speed = 5;
	gamedata->player.fov = 70;
	gamedata->rotation_angle = 3.0;
	gamedata->map = data->map;
	if (gamedata->map == NULL)
		return (FAILURE);
	gamedata->map_width = data->map_columns;
	gamedata->map_height = data->map_rows;
	gamedata->ceiling_colour = create_colour(data->ceiling[0], data->ceiling[1],
			data->ceiling[2], 255);
	gamedata->floor_colour = create_colour(data->floor[0], data->floor[1],
			data->floor[2], 255);
	return (SUCCES);
}
