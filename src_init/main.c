/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:06:50 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/16 14:47:45 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/initialize.h"

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
	char	**split;
	int		size;

	size = ft_strlen(str2);
	split = ft_split(str1, '.');
	if (split == NULL)
		error_exit_input("failed split");
	if (!split[1] || ft_strncmp(split[1], str2, size) != 0)
		error_exit_input("wrong extension");
	free_double(split);
}

// -------------------------------------------------------------

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		check_extension(argv[1], "cub");
		initialize_data(&data);
		process_input(argv[1], &data);
		render(&data);
		free_map(&data);
	}
	else
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	return (0);
}
