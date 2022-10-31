#include "../includes/cube3d.h"

void check_valid_path(char *str, t_data *data)
{
	char **split;
	int fd;

	split = ft_split(str, ' ');

	fd = open(split[1], O_RDONLY);  // if split == NULL -> fd == -1 
	if (fd == -1)
	{
		free_double(split);
		error_exit_input("invalid path");
	}
	free_double(split);
	data->nr_paths++;
}

void check_valid_color(char *str, t_data *data)
{
	int i;
	
	i = 1;

	while (str[i] != '\0')
	{
		if (check_string(str[i], COLOR) == 0)
			error_exit_input("invalid color");
		i++;
	}
	data->nr_colors++;
}

int check_string(char c, const char *array)  // check_row_elem  // checks if the element of a row belongs to the array
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

int check_player_double(char *line)  // checks whether the player is double on a row // obsolete function 
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

int check_row_map(char *line)  // checks whether the row is a map row or not 
{
	// const char row_elements = { ,0,1,N,S,E,W};
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

//--------------------------------------------------------------------------------------------------------------


void find_map_start(int fd, t_data *data)   // finds the line on which map starts 
{
	char *line;
	int row;
	
	while (get_next_line(fd, &line) > 0)
	{
		if (check_row_map(line) == 0)
		{
			data->map_lenght++;
			data->map_row_lenght = ft_strlen(line);
			break;
		}
		data->map_start++;
	}
	data->map_start++;

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
}

void check_store_path(char *line, t_data *data)  // checks if a path is valid and if so storres it - if too many paths error 
{
	char **split;
	int fd;

	split = ft_split(line, ' ');
	// printf("split[0] %s\n", split[0]);
	// printf("split[1] %s\n", split[1]);

	fd = open(split[1], O_RDONLY);  // if split == NULL -> fd == -1 
	// if (fd == -1)
	// {
	// 	free_double(split);
	// 	error_exit_input("invalid path");
	// }

	if (data->nr_paths > 3)
		error_exit_input("too many paths");
	data->paths[data->nr_paths][0] = ft_strdup(split[0]);
	printf("data->paths[data->nr_paths][0] %s\n", data->paths[data->nr_paths][0]);

	data->paths[data->nr_paths][1] = ft_strdup(split[1]);
	printf("data->paths[data->nr_paths][1] %s\n", data->paths[data->nr_paths][1]);

	free_double(split);
	data->nr_paths++;
}

//-------------------------------------------------------

void check_RBG(unsigned char ***array)
{
	int nr;
	int i;

	printf("array[0][1] %s\n", array[0][1]);

	i = 0;
	while (i < 2)
	{
		nr = ft_atoi(array[i][1]);
		if (nr < 0 || nr > 255)
			error_exit_input("invalid color");
		nr = ft_atoi(array[i][2]);
		if (nr < 0 || nr > 255)
			error_exit_input("invalid color");
		nr = ft_atoi(array[i][3]);
		if (nr < 0 || nr > 255)
			error_exit_input("invalid color"); 
		i++;
	}
}

void check_store_color(char *line, t_data *data)
{
	char **split;
	char **split_digits;

	split = ft_split(line, ' ');
	if (split == NULL || !split[1] || split[1] == '\0')
		error_exit_input("failed ft_split");
	split_digits = ft_split(split[1], ',');
	if (split_digits == NULL)
	{
		free_double(split);
		error_exit_input("failed ft_split");
	}

	if (data->nr_colors > 1)
		error_exit_input("too many colors");
	data->colors[data->nr_colors][0] = (unsigned char *)ft_strdup(split[0]);
	printf("data->colors[data->nr_colors][0] %s\n", data->colors[data->nr_colors][0]);

	data->colors[data->nr_colors][1] = (unsigned char *)ft_strdup(split_digits[0]);
	printf("data->colors[data->nr_colors][1] %s\n", data->colors[data->nr_colors][1]);

	data->colors[data->nr_colors][2] = (unsigned char *)ft_strdup(split_digits[1]);
	printf("data->colors[data->nr_colors][2] %s\n", data->colors[data->nr_colors][2]);

	data->colors[data->nr_colors][3] = (unsigned char *)ft_strdup(split_digits[2]);
	printf("data->colors[data->nr_colors][3] %s\n", data->colors[data->nr_colors][3]);

	free_double(split);
	free_double(split_digits);
	check_RBG(data->colors);
}
//-------------------------------------------------------


void check_store_path_color(int fd, t_data *data)
{
	char *line;
	int i;
	int j;

	
	printf("test\n");
	i = 0;
	while (i < data->map_start)
	{
		get_next_line(fd, &line);
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (line[j] != '\n')
		{
			if ((line[j] == 'N' && line[i + 1] == 'O') || (line[j] == 'S' && line[i + 1] == 'O') ||
					(line[j] == 'E' && line[i + 1] == 'A') || (line[j] == 'W' && line[i + 1] == 'E'))
				check_store_path(line, data);
			
			if (line[j] == 'F' || line[j] == 'C')
				check_store_color(line, data);
		}
	}
	if (data->nr_paths < 3 || data->nr_colors < 2)
		error_exit_input("too few paths/colors");
}

//-------------------------------------------------------

// void check_store_map()

int check_input(char *file, t_data *data)
{
	int fd;
	int fd2;

	//open fd
	fd = open_fd(file);
	printf("fd: %d\n", fd);
	// find where map starts 
	find_map_start(fd, data);
	close(fd);
	printf("start map: %d\n", data->map_start);
	printf("lenght map: %d\n", data->map_lenght);
	printf("lenght row: %d\n", data->map_row_lenght);


	
	// reopen fd
	fd2 = open_fd(file);
	printf("fd2: %d\n", fd);

	// check and store path and color
	check_store_path_color(fd2, data);
	// check and store map

	close(fd2);
	free_memory(data);
	return (0);
}



	// while (get_next_line(fd, &line) > 0)
	// {

	// 	i = 0;
	// 	while (line[i] == ' ' || line[i] == '\t')
	// 		i++;
	// 	if (line[i] != '\n')
	// 	{
    //     	printf("test line\n");
	// 		if (check_row_map(line) == 0) // and 
	// 		{
	// 			if (check_player_double(line)!= 0)
	// 				error_exit_input("invalid map input");
	// 			// if (data->map_start == 0)
	// 			// 	data->map_start = data->map_rows;      not actually using ....
	// 			lenght = ft_strlen(line);
	// 			if (data->map_colums < lenght)
	// 				data->map_colums = lenght;
	// 			data->map_rows++; 
	// 		}

	// 		if (check_string(line[i], MAP_PLAYER) == 1)
	// 		{
	// 			if (line[i] == 'N' && line[i + 1] == 'O')
	// 				check_valid_path(line, data);
	// 			if (line[i] == 'S' && line[i + 1] == 'O')
	// 				check_valid_path(line, data);
	// 			if (line[i] == 'E' && line[i + 1] == 'A')
	// 				check_valid_path(line, data);
	// 			if (line[i] == 'W' && line[i + 1] == 'E')
	// 				check_valid_path(line, data);

	// 			if (data->nr_paths < 4 || data->nr_paths > 4)
	// 				error_exit_input("too few/many paths");
	// 		}	

	// 		if (line[i] == 'F' || line[i] == 'C')
	// 		{
	// 			data->nr_colors++;
	// 			if (data->nr_colors < 2 || data->nr_colors > 2)
	// 				error_exit_input("too few/many colors");
	// 		}				
	// 	}
	// }
	// if (data->nr_paths < 3)
	// 	error_exit_input("not enough paths");
	// if (data->nr_colors < 1)
	// 	error_exit_input("not enough colors");
	// close(fd);
	// return (0);
// }

// int i = 0;
// int player = 0;
// int non_line = 0;

// while (line[i] != '\0')
// {
// 	if (line[i] == ' ' || line[i] == '0' || line[i] == '1')
// 		i++;
// 	else if (check_string(line[i], MAP_PLAYER) == 1)
// 	{
// 		if (player == 1)
// 			break ;
// 		else
// 			player = 1;
// 	}
// 	else
// 	{
// 		if (non_line == 0)
// 			non_line = 1;
// 	}
// }

// if (non_line == 1) // --- this is not a map line
// if (non_line == 1 && data->map_start != 0) // --- this is an invalid map as I already started the map 
// if (non_line == 0 && player == 1) // --- this is an invalid map