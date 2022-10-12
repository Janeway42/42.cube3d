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