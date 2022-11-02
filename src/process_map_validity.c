#include "../includes/cube3d.h"

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
