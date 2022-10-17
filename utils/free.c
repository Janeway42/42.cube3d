#include "../includes/cube3d.h"

void free_double(char **str)
{
    char **temp;

    temp = str;
    while (*temp)
    {
        free(temp);
        temp++;
    }
    free(str);
}

void free_memory(t_data *data)
{
    int i;
    int j;

    i = 0;
    if (data->map)
    {
        while (data->map[i] != NULL)
        {
            if (data->map[i])
                free_double(&data->map[i]);
            i++;
        }
        free(data->map);
    }

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 2)
        {
            if (data->paths[i][j])
                free(&data->paths[i][j]);
            j++;
        }
        i++;
    }

    i = 0;
    while (i < 2)
    {
        j = 0;
        while (j < 4)
        {
            if (data->colors[i][j])
                free(&data->paths[i][j]);
            j++;
        }
        i++;
    }
}