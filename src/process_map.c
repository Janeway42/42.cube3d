#include "../includes/cube3d.h"

void print_map(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < data->map_lenght)
    {
        j = 0;
        while (j < data->map_row_lenght)
        {
            printf("%c", data->map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
}



void allocate_memory_map(t_data *data)
{
    int i;

    data->map = malloc(sizeof(char *) * data->map_lenght);
    if (!data->map)
        error_exit_input("failed malloc");
    i = 0;
    while (i < data->map_lenght)
    {
        data->map[i] = malloc(sizeof(char) * (data->map_row_lenght + 1));
        if (!data->map[i])
            error_exit_input("malloc fail");
        data->map[i][data->map_row_lenght] = '\0';
        i++;
    }
}

void copy_row(int i, char *line, t_data *data)
{
    int j;
    int size;
    
    j = 0;
    size = ft_strlen(line);
    while (j < size)
    {
        data->map[i][j] = (line)[j];
        j++;
    }
    while (j < data->map_row_lenght)
    {
        data->map[i][j] = ' ';
        j++;
    }
}

void check_store_map(int fd, char **line, t_data *data)
{
    int i;

    allocate_memory_map(data);

    // first line
    i = 0;
    copy_row(i, *line, data);
    i++;

    // middle of the map 
    while (get_next_line(fd, line) > 0)
    {
        if (i < data->map_lenght && check_row_map(*line) == 1)
            error_exit_input("invalid map");
        copy_row(i, *line, data);
        i++;
    }

    // last line
    if (i < data->map_lenght && check_row_map(*line) == 1)
        error_exit_input("invalid map");
    copy_row(i, *line, data);

    print_map(data);
}
