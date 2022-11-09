#include "../includes/initialize.h"

// function finds the line on which the map starts
// -----------------------------------------------------------

static void	count_line(char *line, t_data *data)
{
	int	row_size;

	row_size = ft_strlen(line);
	if (row_size > data->map_columns)
		data->map_columns = row_size;
	if (row_size != 0)                 //  ??????
		data->map_rows++;
}

static void	find_map_start(int fd, t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[i] == '\0' || (line[i] == 'N' && line[i + 1] == 'O')
			|| (line[i] == 'S' && line[i + 1] == 'O')
			|| (line[i] == 'E' && line[i + 1] == 'A')
			|| (line[i] == 'W' && line[i + 1] == 'E')
			|| line[i] == 'F' || line[i] == 'C')
			data->map_start++;
		else if (check_row_map(line) == 0)
			break ;
		else
			error_exit_input("invalid input/map row");
	}
	data->map_start++;
	data->map_rows++;
	data->map_columns = ft_strlen(line);
	while (get_next_line(fd, &line) > 0)
		count_line(line, data);
	if (line[i] != '\0')
		count_line(line, data);
	printf("rows: %d\n", data->map_rows);
	printf("col: %d\n", data->map_columns);
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
	line = process_path_color(fd, data);
	check_store_map(fd, &line, data);
	close(fd);
	check_map_validity(data);
	return (0);
}
