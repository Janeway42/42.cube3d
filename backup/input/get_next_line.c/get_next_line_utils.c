#include "../includes/get_next_line.h"

static int	copy_string(char **dest, const char *src, int n)
{	
	int	i;

	i = 0;
	if (src[0] != '\0')
	{
		while (src[i] != '\0')
		{
			(*dest)[i + n] = src[i];
			i++;
		}
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size_s1;
	int		size_s2;
	int		i;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!result)
		return (NULL);
	result[size_s1 + size_s2] = '\0';
	i = 0;
	i += copy_string(&result, s1, i);
	i += copy_string(&result, s2, i);
	free(s1);
	return (result);
}

/*
** copies to line from buff up to a specific character: \n
*/

char	*ft_line(const char *str, char c)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** modified strlen to count from a specific character: \n
*/

int	ft_strlength(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

/*
** copies to a new string from a specific character: \n
*/

char	*ft_leftover(const char *str, char c)
{
	char	*dest;
	int		strlen_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strlen_str = ft_strlength(str, '\n');
	dest = malloc(sizeof(char) * (strlen_str + 1));
	if (!dest)
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}