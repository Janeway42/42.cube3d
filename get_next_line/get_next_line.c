#include "../includes/get_next_line.h"

/*
** creates the line to be printed and over writes line for the next round
*/

static char	*create_line(char **line, char *keep, char *buff)
{
	char	*leftover;

	keep = ft_strjoin(keep, buff);
	*line = ft_line(keep, '\n');
	leftover = ft_leftover(keep, '\n');
	free(keep);
	keep = leftover;
	return (keep);
}

/*
** calculates if the saved line contains a '\n'
*/

static int	has_l(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
** creates the last line and frees the saved line. Somehow...
*/

static int	free_line(char **keep, char **line)
{
	if (!*keep)
	{
		*keep = malloc(sizeof(char) * 1);
		if (!keep)
			return (-1);
		*keep[0] = '\0';
	}
	*line = ft_line(*keep, '\0');
	free(*keep);
	*keep = NULL;
	return (0);
}

/*
** calculates bytes read and null terminates the buff
*/

static int	buff_stuff(int fd, char *buff)
{
	int	bytes;

	bytes = read(fd, buff, BUFFER_SIZE);
	if (bytes == -1)
		return (-1);
	buff[bytes] = '\0';
	return (bytes);
}

int	get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	int			bytes;
	static char	*keep;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	bytes = 1;
	while (bytes)
	{
		bytes = buff_stuff(fd, buff);
		if (bytes == 0)
		{
			if (has_l(keep, '\n') == 0)
				return (free_line(&keep, line));
			keep = create_line(line, keep, buff);
			return (1);
		}
		if ((has_l(keep, '\n') == 1 && bytes > 0) || has_l(buff, '\n') == 1)
		{
			keep = create_line(line, keep, buff);
			return (1);
		}
		keep = ft_strjoin(keep, buff);
	}
	return (0);
}