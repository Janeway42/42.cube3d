#include "../includes/cube3d.h"

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
