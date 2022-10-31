#include "../includes/cube3d.h"

void free_double(char **str)
{
    char **temp;

    temp = str;
    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(str);
}

void free_triple(char ***str)
{
    char ***temp;

    temp = str;
    while (*temp)
    {
        free_double(*temp);
        temp++;
    }
    free(temp);
}

// void free_array(char **str, int row, int col)
// {
//     int i;
//     int j;

//     i = 0;
//     while (i < row)
//     {
//         j = 0;
//         while (j < col)
//         {
//             if (str[i][j])
//                 free(str[i][j]);
//             j++;
//         }
//         i++;
//     }
// }

void free_memory(t_data *data)
{
    if (data->map)
        free_triple(data->map);

    if (data->paths)
        free_triple(data->paths);

    if (data->colors)
        free_triple((char ***)data->colors);
}

