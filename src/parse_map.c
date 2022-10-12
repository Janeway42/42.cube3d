#include "../includes/cube3d.h"

void parse_map(char *file, t_data *data)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        error_exit_input("failed to open fd");

    char *line;

    while (get_next_line(fd, &line) > 0)
    {


    }
}



int row = 0;

while (get_next_line(fd, &line) > 0)
{
    char **split_line = ft_split(line, ' ');

    if (split_line != NULL)
    {
        if (ft_strcmp(split_line[0], "NO") == 0)
        else if (ft_strcmp(split_line[0], "SO") == 0)
        else if (ft_strcmp(split_line[0], "WE") == 0)
        else if (ft_strcmp(split_line[0], "EA") == 0)
            if (nr_paths > 4)
                error_exit_input("too many paths");
        

        else if (ft_strcmp(split_line[0], "F") == 0)
        else if (ft_strcmp(split_line[0], "C") == 0)
            if (nr_colors > 2)
                error_exit_input("too many colors");

        else if ()  // map 
        {
            while ()
        }

        else
            error_exit_input("something's not quite right with this file");

    
    }
    free_double(split_line);
}













int check_whiteline(char **line)
{
    int i;

    i = 0;
    while (*line[i] != '\0')
    {
        if (*line[i] != '\n' || *line[i] != ' ' || *line[i] != '\t')
            return (1);
        i++;
    }
    return (0);
}

int check_map_line(char **line)
{
    int i;

    i = 0;
    while (*line[i] != '\0')
    {
        if (*line[i] == ' ' || *line[i] == '1' || *line[i] == '0' || *line[i] == 'N' || *line[i] == 'S' || *line[i] == 'W' || *line[i] 'E')
            i++;
        else
            return (1);
    }
    return (0);
}

int rows = 1;
int map_start;
int map

while (get_next_line(fd, &line) > 0)
{
    if (check_whiteline(line) == 1)
    {
        if (*line[0] == 'N' || *line[0] == 'S' || *line[0] == 'W' || *line[0] 'E')
            // add path
        else if ()

    }
    rows++;  // ? do I still neeed? 
} 