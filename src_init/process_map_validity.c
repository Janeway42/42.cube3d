/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_map_validity.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:07:08 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/11 17:07:09 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/initialize.h"

// if map[i][j] == 0  || map[i][j] == NSEW -> if neighbours == ' ' error 
// ----------------------------------------------------------------

static void	element_verification(char **map, int i, int j)
{
	if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
		error_exit_input("invalid map");
}

static void	row_verification(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
			error_exit_input("invalid map");
		j++;
	}
}

// the middle section verrifies first the first element, 
// then the entire middle section and lastly the final elem of the row
// -------------------------------------------------------------------

static void	process_player(int i, int j, t_data *data)
{
	if (data->player == 1)
		error_exit_input("invalid map");
	data->player = 1;
	if (data->map[i][j] == 'N')
		data->player_direction = 90;
	if (data->map[i][j] == 'S')
		data->player_direction = 270;
	if (data->map[i][j] == 'E')
		data->player_direction = 0;
	if (data->map[i][j] == 'W')
		data->player_direction = 180;
	data->player_pos[0] = i + 0.5;
	data->player_pos[1] = j + 0.5;
}

static void	middle_section(char **map, int i, t_data *data)
{
	int	j;

	j = 0;
	element_verification(data->map, i, j);
	j++;
	while (j < data->map_columns)
	{
		if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
		{
			if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
				map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
				map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ' ||
				map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
				error_exit_input("invalid map");
			if (check_player(map[i][j], MAP_PLAYER) == 1)
				process_player(i, j, data);
		}
		j++;
	}
	element_verification(data->map, i, j);
}

// if map[i][j] == 0  || map[i][j] == NSEW -> if neighbours == ' ' error 
// if map[i][j] == NSEW -> if data->player == 0 then data->player == 1
//                      -> if data->player == 1 then error 
// -----------------------------------------------------------------
// checking in order: the first line, the middle section 
//                    and the last line

void	check_map_validity(t_data *data)
{
	int	i;

	i = 0;
	row_verification(data->map, i);
	i++;
	while (i < (data->map_rows - 1))
	{
		middle_section(data->map, i, data);
		i++;
	}
	row_verification(data->map, i);
	if (data->player == 0)
		error_exit_input("invalid map");
}
