#ifndef CUBE3D_H
#define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "libft.h"
#include "get_next_line.h"

#define MAP_ROW = { ,0,1,N,S,E,W}
#define MAP_PLAYER = {N,S,E,W}

typedef struct  s_data
{
    char paths[4][2];  // paths - 4 arrays of 2 elements 
    unsigned char colors[2][4];  // colors - 2 arrays of 2 elements 
    char **map;  // map  - 2d array  - create padding

    int nr_paths;
    int nr_colors;
    int map_rows;
    int map_colums;
    int player;
    int map_start;  //??
}               t_data;

/*
// ---------------- Verify ---------------------- 
*/

int open_fd(char *file);
int check_input(int fd, t_data *data);

/*
// ---------------- Free ---------------------- 
*/

void free_double(char **str);

/*
// ---------------- Error ---------------------- 
*/

void error_exit_input(char *str);


#endif