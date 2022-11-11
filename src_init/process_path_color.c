/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_path_color.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:07:19 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/11 17:11:18 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/initialize.h"

static unsigned char	verify_color_elem(char *str)
{
	unsigned int	temp;
	char			*temp_str;

	temp = (unsigned int)ft_atoi(str);
	temp_str = ft_itoa(temp);
	if (ft_strncmp(temp_str, str, ft_strlen(str) != 0))
		error_exit_input("wrong color input");
	if (temp > 255)
		error_exit_input("invalid color");
	free(temp_str);
	return ((unsigned char)temp);
}

// static void	process_color(char *line, unsigned char **str, t_data *data)
static void	process_color(char *line, unsigned char array[], t_data *data)
{
	char	**split;
	char	**split_digits;

	split = ft_split(line, ' ');
	if (split == NULL || !split[1] || split[1] == NULL)
		error_exit_input("failed ft_split");
	split_digits = ft_split(split[1], ',');
	if (split_digits == NULL)
	{
		free_double(split);
		error_exit_input("failed ft_split");
	}
	if (data->nr_colors > 1)
		error_exit_input("too many colors");
	array[0] = verify_color_elem(split_digits[0]);
	array[1] = verify_color_elem(split_digits[1]);
	array[2] = verify_color_elem(split_digits[2]);
	free_double(split);
	free_double(split_digits);
	data->nr_colors++;
}

// checks if a path is valid and if so storres it - if too many paths error 
//-----------------------------------------------------------------------------

static void	process_path(char *line, char **str, t_data *data)
{
	char	**split;
	int		fd;

	split = ft_split(line, ' ');
	fd = open(split[1], O_RDONLY);
	if (fd == -1)
	{
		free_double(split);
		error_exit_input("invalid path");
	}
	check_extension(split[1], "png");
	if (data->nr_paths > 3)
		error_exit_input("too many paths");
	*str = ft_strdup(split[1]);
	free_double(split);
	data->nr_paths++;
}

//-------------------------------------------------------

static void	process_distribution(char *line, int j, t_data *data)
{
	if (line[j] == 'N' && line[j + 1] == 'O')
		process_path(line, &data->north, data);
	if (line[j] == 'S' && line[j + 1] == 'O')
		process_path(line, &data->south, data);
	if (line[j] == 'E' && line[j + 1] == 'A')
		process_path(line, &data->east, data);
	if (line[j] == 'W' && line[j + 1] == 'E')
		process_path(line, &data->west, data);
	if (line[j] == 'F')
		process_color(line, data->floor, data);
	if (line[j] == 'C')
		process_color(line, data->ceiling, data);
}

char	*process_path_color(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	get_next_line(fd, &line);
	while (i < data->map_start - 1)
	{
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (line[j] != '\0')
			process_distribution(line, j, data);
		i++;
		free(line);
		get_next_line(fd, &line);
	}
	if (data->nr_paths < 3 || data->nr_colors < 2)
		error_exit_input("too few paths/colors");
	return (line);
}
