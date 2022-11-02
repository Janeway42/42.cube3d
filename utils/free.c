#include "../includes/cube3d.h"

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

void	free_memory(t_data *data)
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
	if (data->north)
		free_double(data->north);
	if (data->south)
		free_double(data->south);
	if (data->east)
		free_double(data->east);
	if (data->west)
		free_double(data->west);
	if (data->floor)
		free_double((char **)data->floor);
	if (data->celeing)
		free_double((char **)data->celeing);
}
