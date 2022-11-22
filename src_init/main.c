/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:06:50 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/21 14:05:16 by hman          ########   odam.nl         */
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

static void	initialize_data(t_data *data)
{
	int	i;

	i = 0;
	data->nr_paths = 0;
	data->nr_colors = 0;
	data->map_start = 0;
	data->map_rows = 0;
	data->map_columns = 0;
	data->player = 0;
	data->player_direction = -1;
	data->north = NULL;
	data->south = NULL;
	data->east = NULL;
	data->west = NULL;
	while (i < 6)
	{
		data->true_input[i] = false;
		i++;
	}
}

// -------------------------------------------------------------

void	check_extension(char *str1, char *str2)
{
	int	size1;
	int	size2;
	int	i;

	i = 1;
	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	while (size1 - i > -1 && size2 - i > -1)
	{
		if (str1[size1 - i] == str2[size2 - i])
		{
			if (size2 - i == 0)
				break ;
			i++;
		}
		else
			error_exit_input("wrong extension");
	}
}

// -------------------------------------------------------------
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (ft_strlen(argv[1]) == 0)
	{
		printf("No map to read\n");
		return (1);
	}
	check_extension(argv[1], ".cub");
	initialize_data(&data);
	process_input(argv[1], &data);
	render(&data);
	free_map(&data);
	return (0);
}
