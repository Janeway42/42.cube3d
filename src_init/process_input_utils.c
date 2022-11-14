/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_input_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:06:56 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/14 17:05:03 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/initialize.h"

int	open_fd(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit_input("failed to open fd");
	return (fd);
}

// checks if the element of a row belongs to the array
// ----------------------------------------------------------------------

int	check_player(char c, const char *array)
{
	int	i;

	i = 0;
	while (array[i] != '\0')
	{
		if (array[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// checks whether the row is a map row or not 
// ----------------------------------------------------------------------

int	check_row_map(char *line)
{
	int	i;
	int	j;
	int	exists;

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

// checks whether there is a comma at the end of the color input
// ----------------------------------------------------------------------

void	check_end_comma(char *str)
{
	int	length;

	length = ft_strlen(str);
	while (length > -1 && ft_isdigit(str[length]) == 0)
	{
		if (str[length] == ',' && str[length - 1] != ',')
			error_exit_input("invalid color input, too many commas");
		length--;
	}
}

// checks whether all paths and all colors are present in the input
// ----------------------------------------------------------------------

void	true_input_verify(bool array[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (array[i] == false)
			error_exit_input("missing path/color input");
		i++;
	}
}
