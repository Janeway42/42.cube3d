#include "../includes/cube3d.h"

void allocate_map_memory(t_data *data)
{
    int i;

    i = 0;
    map = malloc(sizeof(char*) * (data->map_rows + 3));
    if (!map)
        error_exit_input("failed map malloc");
    map[data->map_rows + 2] = NULL;
    while (i < (data->map_rows + 3))
    {
        map[i] = malloc(sizeof(char) * (data->map_colums + 3));
        if (!map[i])
        {
            while (i > -1)
            {
                free(map[i]);
                i--;
            }
            free(map);
            error_exit_input("failed map malloc");
        }
        map[i][data->map_colums + 2] = '\0';
        i++;
    }    
}

void parse_map(int fd, t_data *data)
{
    char *line;
    int i;
    int row;
    int paths;
    int colors;
    
    paths = 0;
    colors = 0;
    row = 0;
    i = 0;

    while (map[0][i] != '\0')
    {
        map[0][i] = ' ';
        i++
    }
    row++;

    allocate_map_memory(data); 

    while (get_next_line(fd, &line) > 0)
    {
        i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] != '\n')
        {
			if (check_row(line) == 0)
			{   
                i = 0;
                map[row][i] = ' ';
                while (line[i] != '\0')
                {
                    map[row][i + 1] = line[i];
                    i++;
                }
                while (map[row][i + 1] != '\0')
                {
                    map[row][i + 1] = ' ';
                    i++;
                }
                row++;
            }

    		if (check_string(line[i], MAP_PLAYER))
    		{
                char **split_line;

                split_line = ft_split(line, ' ');
                if (split_line == NULL)
                {
                    //free stuff
                    error_exit_input("failed ft_split");
                }
			    if (line[i] == 'N' && line[i + 1] == 'O')
                {
                    while (i < 2)
                    {
                        data->paths[paths][i] = ft_strdup(split_line[i]);  // don't forget free
                        i++;
                    }
                }
			    else if (line[i] == 'S' && line[i + 1] == 'O')
			    {}
			    else if (line[i] == 'E' && line[i + 1] == 'A')
			    {}
			    else if (line[i] == 'W' && line[i + 1] == 'E')
			    {}
                free_double(split_line);
                paths++;
            }

            if (line[i] == 'F' || line[i] == 'C')
            {
                char **split_line;
                char **split_num;

                split_line = ft_split(line, ' ');
                if (split_line == NULL);
                {
                    //free stuff
                    error_exit_input("failed ft_split");
                }
                data->colors[colors][0] = ft_strdup(split_line[0]);
                
                split_num = ft_split(split_line[1], ',');
                if (split_num == NULL)
                {
                    //free stuff
                    error_exit_input("failed ft_split");
                }

                i = 0;
                while (i < 4)
                {
                    data->colors[colors][i + 1] = ft_strdup(split_num[i]);
                    i++;
                }

                free_double(split_num);
                free_double(split_line);
                colors++;
            }
        }

        i = 0;
        while (map[row][i] != '\0')
        {
          map[row][i] = ' ';
          i++
        }
    }
}
