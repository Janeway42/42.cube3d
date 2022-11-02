#include "../includes/cube3d.h"

// if map[i][j] == 0 -> if neighbours == ' ' error 
// if map[i][j] == NSEW -> if data->player == 0 then data->player == 1 and if neighbours == ' ' error
//                      -> if data->player == 1 then error 

void	check_map_validity(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	// first line
	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
			error_exit_input("invalid map");
		j++;
	}
	i++;

	// middle section
	while (i < (data->map_rows - 1))
	{
		if (map[i][0] == '0' || check_player(map[i][0], MAP_PLAYER) == 1)
			error_exit_input("invalid map");
		j = 1;

		while (j < data->map_columns)
		{
			if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
			{
				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
					map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
					map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' ' ||
					map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ')
					error_exit_input("invalid 1 map");
				if (check_player(map[i][j], MAP_PLAYER) == 1)
				{
					if (data->player == 1)
						error_exit_input("invalid map");
					data->player = 1;
					data->player_direction = map[i][j];
				}
			}
			j++;
		}
		if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
			error_exit_input("invalid map");
		i++;
	}

    // last line   
	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == '0' || check_player(map[i][j], MAP_PLAYER) == 1)
			error_exit_input("invalid map");
		j++;
	}

	if (data->player == 0)
		error_exit_input("invalid map");
}
