#include "../includes/cube3d.h"

// void check_valid_path(char *str, t_data *data)
// {
// 	char **split;
// 	int fd;

// 	split = ft_split(str, ' ');

// 	fd = open(split[1], O_RDONLY);  // if split == NULL -> fd == -1 
// 	if (fd == -1)
// 	{
// 		free_double(split);
// 		error_exit_input("invalid path");
// 	}
// 	free_double(split);
// 	data->nr_paths++;
// }

// void check_valid_color(char *str, t_data *data)
// {
// 	int i;
	
// 	i = 1;

// 	while (str[i] != '\0')
// 	{
// 		if (check_string(str[i], COLOR) == 0)
// 			error_exit_input("invalid color");
// 		i++;
// 	}
// 	data->nr_colors++;
// }

// int check_string(char c, const char *array)  // check_row_elem  // checks if the element of a row belongs to the array
// {
// 	int i;

// 	i = 0;
// 	while (array[i] != '\0')
// 	{
// 		if (array[i] == c)
// 			return (1);
// 	}
// 	return (0);
// }

// int check_player_double(char *line)  // checks whether the player is double on a row // obsolete function 
// {
// 	// const char players = {N,S,E,W}
// 	int i;
// 	int k;
// 	int duplicat;

// 	i = 0;
// 	duplicat = 0;

// 	while (line[i] != '\0')
// 	{
// 		if (check_string(line[i], MAP_PLAYER) == 1)
// 		{
// 			k = i - 1;
// 			while (k > -1)
// 			{
// 				if (line[k] == line[i])
// 					return (1);
// 				k--;
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

//--------------------------------------------------------------------------------------------------------------

int check_row_map(char *line)  // checks whether the row is a map row or not 
{
	int i;
	int j;
	int exists;

	i = 0;
	if (line[i] == '\0')
		return (1);
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



void find_map_start(int fd, t_data *data)   // finds the line on which map starts 
{
	char *line;
	int row;
	int i = 0;

	while (get_next_line(fd, &line) > 0)
	{
		if(line[i] == '\0' || (line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i + 1] == 'O') || 
				(line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line[i + 1] == 'E') || 
				line[i] == 'F' || line[i] == 'C')
				data->map_start++;
		else
			break;
	}
	data->map_start++;

	data->map_row_lenght = ft_strlen(line);
	while (get_next_line(fd, &line) > 0)
	{
		row = ft_strlen(line);
		if (row > data->map_row_lenght)
			data->map_row_lenght = row;
		data->map_lenght++;
	}
	row = ft_strlen(line);
	if (row > data->map_row_lenght)
		data->map_row_lenght = row;
	data->map_lenght++;	

	printf("start: %d\n", data->map_start);
	printf("map lenght: %d\n", data->map_lenght);

	
	// while (get_next_line(fd, &line) > 0)
	// {
	// 	if (check_row_map(line) == 0)
	// 	{
	// 		data->map_lenght++;
	// 		data->map_row_lenght = ft_strlen(line);
	// 		break;
	// 	}
	// 	data->map_start++;
	// }
	// data->map_start++;

	// while (get_next_line(fd, &line) > 0)
	// {
	// 	row = ft_strlen(line);
	// 	if (row > data->map_row_lenght)
	// 		data->map_row_lenght = row;
	// 	data->map_lenght++;
	// }
	// row = ft_strlen(line);
	// if (row > data->map_row_lenght)
	// 	data->map_row_lenght = row;
	// data->map_lenght++;	
}



//-------------------------------------------------------


char *check_store_path_color(int fd, t_data *data)
{
	char *line;
	int i;
	int j;

	i = 0;
	while (i < data->map_start)
	{
		get_next_line(fd, &line);
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (line[j] != '\n')
		{
			if (line[j] == 'N' && line[j + 1] == 'O')
				check_store_path(line, data->north, data);
			if (line[j] == 'S' && line[j + 1] == 'O')
				check_store_path(line, data->south, data);
			if (line[j] == 'E' && line[j + 1] == 'A')
				check_store_path(line, data->east, data);
			if (line[j] == 'W' && line[j + 1] == 'E')
				check_store_path(line, data->west, data);
			
			if (line[j] == 'F')
				check_store_color(line, data->floor, data);
			if (line[j] == 'C')
				check_store_color(line, data->celeing, data);
		}
		i++;
	}
	// printf("data->nr_paths: %d\n", data->nr_paths);
	// printf("data->nr_columns: %d\n", data->nr_colors);
	if (data->nr_paths < 3 || data->nr_colors < 2)
		error_exit_input("too few paths/colors");
	return (line);
}

//-------------------------------------------------------

int process_input(char *file, t_data *data)
{
	int fd;
	char *line;

	fd = open_fd(file);
	find_map_start(fd, data);
	close(fd);
	// printf("start map: %d\n", data->map_start);
	// printf("lenght map: %d\n", data->map_lenght);
	// printf("lenght row: %d\n", data->map_row_lenght);

	fd = open_fd(file);
	line = check_store_path_color(fd, data);
	check_store_map(fd, &line, data);

	close(fd);
	free_memory(data);
	return (0);
}
