#include "../includes/cube3d.h"

static void	check_rbg(unsigned char **array)
{
	int	nr;

	nr = ft_atoi((char *)array[1]);
	if (nr < 0 || nr > 255)
		error_exit_input("invalid color");
	nr = ft_atoi((char *)array[2]);
	if (nr < 0 || nr > 255)
		error_exit_input("invalid color");
	nr = ft_atoi((char *)array[3]);
	if (nr < 0 || nr > 255)
		error_exit_input("invalid color");
}

void	check_store_color(char *line, unsigned char **str, t_data *data)
{
	char	**split;
	char	**split_digits;

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
	str[0] = (unsigned char *)ft_strdup(split[0]);
	printf("str[0] %s\n", str[0]);  // remove --------------------------------
	str[1] = (unsigned char *)ft_strdup(split_digits[0]);
	printf("str[1] %s\n", str[1]);  // remove --------------------------------
	str[2] = (unsigned char *)ft_strdup(split_digits[1]);
	printf("str[2] %s\n", str[2]);  // remove --------------------------------
	str[3] = (unsigned char *)ft_strdup(split_digits[2]);
	printf("str[3] %s\n", str[3]);  // remove --------------------------------
	free_double(split);
	free_double(split_digits);
	check_rbg(str);
	data->nr_colors++;
}

// checks if a path is valid and if so storres it - if too many paths error 
//-----------------------------------------------------------------------------

void	check_store_path(char *line, char **str, t_data *data)
{
	char	**split;
	int		fd;

	split = ft_split(line, ' ');
	
	// this needs to be uncommented - unable to test with it active (need valid jpeg)
	fd = open(split[1], O_RDONLY);  // if split[1] == NULL -> fd == -1 
	// if (fd == -1)
	// {
	// 	free_double(split);
	// 	error_exit_input("invalid path");
	// }

	check_extension(split[1], "jpeg");
	if (data->nr_paths > 3)
		error_exit_input("too many paths");
	str[0] = ft_strdup(split[0]);
	printf("str %s\n", str[0]);  // remove --------------------------------
	str[1] = ft_strdup(split[1]);
	printf("str %s\n", str[1]);  // remove --------------------------------
	free_double(split);
	data->nr_paths++;
}

//-------------------------------------------------------

char	*check_store_path_color(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		j;

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
	if (data->nr_paths < 3 || data->nr_colors < 2)
		error_exit_input("too few paths/colors");
	return (line);
}
