#ifndef CUBE3D_H
#define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "libft.h"
#include "get_next_line.h"


typedef struct  s_data
{
    char paths[4][2];  // paths - 4 arrays of 2 elements 
    unsigned char colors[2][4];  // colors - 2 arrays of 2 elements 
    char **map;  // map  - 2d array  - create padding

    int nr_paths;
    int nr_colors;
}               t_data;

/*
// ---------------- Free ---------------------- 
*/

void free_double(char **str);

/*
// ---------------- Error ---------------------- 
*/

void error_exit_input(char *str);


#endif