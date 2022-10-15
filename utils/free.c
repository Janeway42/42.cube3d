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
    if (map)
    {
        while (map[i] != NULL)
        {
            if (map[i])
                free_double(map[i]);
            i++;
        }
        free(map);
    }

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 2)
        {
            if (path[i][[j]])
                free(path[i][j]);
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
            if (colors[i][[j]])
                free(path[i][j]);
            j++;
        }
        i++;
    }
}