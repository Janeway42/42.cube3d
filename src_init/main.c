#include "../includes/initialize.h"

static void	initialize_data(t_data *data)
{
	data->nr_paths = 0;
	data->nr_colors = 0;
	data->map_start = 0;
	data->map_rows = 0;
	data->map_columns = 0;
	data->player = 0;
	data->player_direction = -1;
	data->north = NULL;
	data->south = NULL;
	data->east = NULL;
	data->west = NULL;
}

// -------------------------------------------------------------

void	check_extension(char *str1, char *str2)
{
	char	**split;
	int		size;

	size = ft_strlen(str2);
	split = ft_split(str1, '.');
	if (split == NULL)
		error_exit_input("failed split");
	if (!split[1] || ft_strncmp(split[1], str2, size) != 0)
		error_exit_input("wrong extension");
	free_double(split);
}

// -------------------------------------------------------------

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		check_extension(argv[1], "cub");
		initialize_data(&data);
		process_input(argv[1], &data);
		render(&data);
	}
	else
	{
		printf("Wrong number of argumnets\n");
		return (1);
	}
	// free_map(&data);
	system("leaks -q cub3d");
	return (0);
}
