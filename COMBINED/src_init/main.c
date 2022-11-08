#include "../includes/initialize.h"

unsigned char	**assign_memory(void)
{
	unsigned char	**str;
	int				i;

	str = malloc(sizeof(char **) * 3);
	if (!str)
		error_exit_input("malloc fail");
	str[2] = NULL;
	i = 0;
	while (i < 2)
	{
		str[i] = malloc(sizeof(char *) * 1);
		if (!str[i])
			error_exit_input("malloc fail");
		str[i][0] = '\0';
		i++;
	}
	return (str);
}

static void	initialize_data(t_data *data)
{
	data->nr_paths = 0;
	data->nr_colors = 0;
	data->player = 0;
	data->map_start = 0;
	data->map_rows = 0;
	data->map_columns = 0;
	data->north = (char **)assign_memory();
	data->south = (char **)assign_memory();
	data->east = (char **)assign_memory();
	data->west = (char **)assign_memory();
	data->floor = assign_memory();
	data->celeing = assign_memory();
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
