#include "../includes/cube3d.h"

static void check_RBG(unsigned char **array)
{
	int nr;

	nr = ft_atoi((char *)array[1]);
	if (nr < 0 || nr > 255)
		error_exit_input("invalid color");
	nr = ft_atoi((char *)array[2]);
	if (nr < 0 || nr > 255)
		error_exit_input("invalid color");
	nr = ft_atoi((char *)array[3]);
	if (nr < 0 || nr > 255)
		error_exit_input("invalid color"); 
}

void check_store_color(char *line, unsigned char **str, t_data *data)
{
	char **split;
	char **split_digits;

	split = ft_split(line, ' ');
	if (split == NULL || !split[1] || split[1] == '\0')
		error_exit_input("failed ft_split");
	split_digits = ft_split(split[1], ',');
	if (split_digits == NULL)
	{
		free_double(split);
		error_exit_input("failed ft_split");
	}

	if (data->nr_colors > 1)
		error_exit_input("too many colors");
	str[0] = (unsigned char *)ft_strdup(split[0]);
	printf("str[0] %s\n", str[0]);

	str[1] = (unsigned char *)ft_strdup(split_digits[0]);
	printf("str[1] %s\n", str[1]);

	str[2] = (unsigned char *)ft_strdup(split_digits[1]);
	printf("str[2] %s\n", str[2]);

	str[3] = (unsigned char *)ft_strdup(split_digits[2]);
	printf("str[3] %s\n", str[3]);

	free_double(split);
	free_double(split_digits);
	check_RBG(str);
	data->nr_colors++;
}

void check_store_path(char *line, char **str, t_data *data)  // checks if a path is valid and if so storres it - if too many paths error 
{
	char **split;
	int fd;

	split = ft_split(line, ' ');

	fd = open(split[1], O_RDONLY);  // if split == NULL -> fd == -1 
	// if (fd == -1)
	// {
	// 	free_double(split);
	// 	error_exit_input("invalid path");
	// }

	if (data->nr_paths > 3)
		error_exit_input("too many paths");
	str[0] = ft_strdup(split[0]);
	printf("str %s\n", str[0]);

	str[1] = ft_strdup(split[1]);
	printf("str %s\n", str[1]);

	free_double(split);
	data->nr_paths++;
}