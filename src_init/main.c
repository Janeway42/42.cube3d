#include "../includes/initialize.h"

char	*assign_memory(void)
{
	char	*str;
	int				i;

	str = malloc(sizeof(char *) * 3);
	if (!str)
		error_exit_input("malloc fail");
	str[2] = '\0';
	return (str);
}

static void	initialize_data(t_data *data)
{
	data->nr_paths = 0;
	data->nr_colors = 0;
	data->map_start = 0;
	data->map_rows = 0;
	data->map_columns = 0;
	data->player = 0;
	data->player_direction = -1;
	data->north = assign_memory();
	data->south = assign_memory();
	data->east = assign_memory();
	data->west = assign_memory();
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
	free(split);
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
	return (0);
}
