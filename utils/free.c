/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:08:17 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/11 17:08:18 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/initialize.h"

void	free_double(char **str)
{
	char	**temp;

	temp = str;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(str);
}

void	free_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->map_rows)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}
