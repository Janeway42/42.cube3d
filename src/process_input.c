#include "../includes/cube3d.h"

// function finds the line on which the map starts
// -----------------------------------------------------------

static void	find_map_start(int fd, t_data *data)
{
	char	*line;
	int		row;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[i] == '\0' || (line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i + 1] == 'O')
			|| (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line[i + 1] == 'E')
			|| line[i] == 'F' || line[i] == 'C')
			data->map_start++;
		else if (check_row_map(line) == 0)
			break ;
		else
			error_exit_input("invalid input/map");
	}
	data->map_start++;
	data->map_rows++;
	data->map_columns = ft_strlen(line);
	while (get_next_line(fd, &line) > 0)
	{
		row = ft_strlen(line);
		if (row > data->map_columns)
			data->map_columns = row;
		data->map_rows++;
	}
	if (line[i] != '\0')
	{
		row = ft_strlen(line);
		if (row > data->map_columns)
			data->map_columns = row;
		data->map_rows++;
	}	
}

//-------------------------------------------------------

int	process_input(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open_fd(file);
	find_map_start(fd, data);
	close(fd);

	fd = open_fd(file);
	line = check_store_path_color(fd, data);
	check_store_map(fd, &line, data);
	close(fd);

	check_map_validity(data->map, data);

	free_memory(data);
	return (0);
}
