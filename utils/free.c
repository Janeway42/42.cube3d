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
