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
    char **north;
    char **south;
    char **east;
    char **west;
    unsigned char **floor;
    unsigned char **celeing;

    char **map;  // map  - 2d array   

    int nr_paths;
    int nr_colors;
    char player_direction;
    int player;
    int map_start;
    int map_rows;
    int map_columns;
}               t_data;

/*
// ---------------- Verify & Parsing---------------------- 
*/

int open_fd(char *file);
int check_row_map(char *line);
void check_extension(char *str1, char *str2);
int check_player(char c, const char *array);
int process_input(char *file, t_data *data);
char *check_store_path_color(int fd, t_data *data);
void check_store_path(char *line, char **str, t_data *data);
void check_store_color(char *line, unsigned char **str, t_data *data);
void check_store_map(int fd, char **line, t_data *data);
void check_map_validity(char **map, t_data *data);

/*
// ---------------- Free ---------------------- 
*/

void free_double(char **str);
void free_memory(t_data *data);

/*
// ---------------- Error ---------------------- 
*/

void error_exit_input(char *str);

#endif