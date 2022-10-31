#ifndef CUBE3D_H
#define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "libft.h"
#include "get_next_line.h"

#define MAP_ROW " 01NSEW"
#define MAP_PLAYER "NSEW"
#define COLOR "0123456789,"

typedef struct  s_data
{
    char ***paths;
    unsigned char ***colors;
    char ***map;  // map  - 2d array  - create padding
    
    // char paths[4][2];  // paths - 4 arrays of 2 elements 
    // unsigned char colors[2][4];  // colors - 2 arrays of 2 elements 

    int nr_paths;
    int nr_colors;
    int map_rows;
    int map_colums;
    int player;
    int map_start;
    int map_lenght;
    int map_row_lenght;
}               t_data;

/*
// ---------------- Verify ---------------------- 
*/

int open_fd(char *file);
int check_input(char *file, t_data *data);
int check_row_map(char *line);
int check_string(char c, const char *array);

/*
// ---------------- Parsing ---------------------- 
*/

void parse_map(int fd, t_data *data);

/*
// ---------------- Free ---------------------- 
*/

void free_double(char **str);
void free_triple(char ***str);
void free_memory(t_data *data);


/*
// ---------------- Error ---------------------- 
*/

void error_exit_input(char *str);


#endif