#include "../includes/cube3d.h"

void	print_map(t_data *data)    // remove -------------------------------------
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_rows)
	{
		j = 0;
		while (j < data->map_columns)
		{
			printf("%c", data->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

static void	allocate_memory_map(t_data *data)
{
	int	i;

	data->map = malloc(sizeof(char *) * data->map_rows);
	if (!data->map)
		error_exit_input("failed malloc");
	i = 0;
	while (i < data->map_rows)
	{
		data->map[i] = malloc(sizeof(char) * (data->map_columns + 1));
		if (!data->map[i])
			error_exit_input("malloc fail");
		data->map[i][data->map_columns] = '\0';
		i++;
	}
}

static void	copy_row(int i, char *line, t_data *data)
{
	int	j;
	int	size;

	j = 0;
	size = ft_strlen(line);
	while (j < size)
	{
		data->map[i][j] = (line)[j];
		j++;
	}
	while (j < data->map_columns)
	{
		data->map[i][j] = ' ';
		j++;
	}
}

void	check_store_map(int fd, char **line, t_data *data)
{
	int	i;

	i = 0;
	allocate_memory_map(data);

	copy_row(i, *line, data); // first line
	i++;

	while (get_next_line(fd, line) > 0) // middle of the map 
	{
		if (i < data->map_rows && check_row_map(*line) == 1)
			error_exit_input("invalid map");
		copy_row(i, *line, data);
		i++;
	}

	if (check_row_map(*line) == 1) // last line    /// i < data->rows ??//
		error_exit_input("invalid input");
	copy_row(i, *line, data);

	print_map(data);
}
