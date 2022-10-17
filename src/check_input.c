#include "../includes/cube3d.h"

int check_string(char c, const char *array)
{
	int i;

	i = 0;
	while (array[i] != '\0')
	{
		if (array[i] == c)
			return (1);
	}
	return (0);
}

int check_player_double(char *line)
{
	// const char players = {N,S,E,W}
	int i;
	int k;
	int duplicat;

	i = 0;
	duplicat = 0;

	while (line[i] != '\0')
	{
		if (check_string(line[i], MAP_PLAYER) == 1)
		{
			k = i - 1;
			while (k > -1)
			{
				if (line[k] == line[i])
					return (1);
				k--;
			}
		}
		i++;
	}
	return (0);
}

int check_row(char *line)
{
	// const char row_elements = { ,0,1,N,S,E,W};
	int i;
	int j;
	int exists;

	i = 0;
	while (line[i] != '\0')
	{
		j = 0;
		exists = 0;
		while (MAP_ROW[j] != '\0')
		{
			if (line[i] == MAP_ROW[j])
				exists = 1;
			j++;				
		}
		if (exists == 0)
			return (1); 
		i++;
	}
	return (0);
}

int check_input(int fd, t_data *data)
{
	char *line;
	int i;
	int lenght;

	while (get_next_line(fd, &line) > 0)
	{

		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != '\n')
		{
        	printf("test line\n");
			if (check_row(line) == 0)
			{
				if (check_player_double(line)!= 0)
					error_exit_input("invalid map input");
				// if (data->map_start == 0)
				// 	data->map_start = data->map_rows;      not actually using ....
				lenght = ft_strlen(line);
				if (data->map_colums < lenght)
					data->map_colums = lenght;
				data->map_rows++; 
			}

			if (check_string(line[i], MAP_PLAYER) == 1)
			{
				if (line[i] == 'N' && line[i + 1] == 'O')
					data->nr_paths++;
				if (line[i] == 'S' && line[i + 1] == 'O')
					data->nr_paths++;
				if (line[i] == 'E' && line[i + 1] == 'A')
					data->nr_paths++;
				if (line[i] == 'W' && line[i + 1] == 'E')
					data->nr_paths++;

				if (data->nr_paths > 3)
					error_exit_input("too many paths");
			}	

			if (line[i] == 'F' || line[i] == 'C')
			{
				data->nr_colors++;
				if (data->nr_colors > 1)
					error_exit_input("too many colors");
			}				
		}
	}
	if (data->nr_paths < 3)
		error_exit_input("not enough paths");
	if (data->nr_colors < 1)
		error_exit_input("not enough colors");
	close(fd);
	return (0);
}

int i = 0;
int player = 0;
int non_line = 0;

while (line[i] != '\0')
{
	if (line[i] == ' ' || line[i] == '0' || line[i] == '1')
		i++;
	else if (check_string(line[i], MAP_PLAYER) == 1)
	{
		if (player == 1)
			break ;
		else
			player = 1;
	}
	else
	{
		if (non_line == 0)
			non_line = 1;
	}
}

if (non_line == 1) // --- this is not a map line
if (non_line == 1 && data->map_start != 0) // --- this is an invalid map as I already started the map 
if (non_line == 0 && player == 1) // --- this is an invalid map