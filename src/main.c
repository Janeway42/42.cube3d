#include "../includes/cube3d.h"

int open_fd(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        error_exit_input("failed to open fd");
    return (fd);
}

static void initialize_data(t_data *data)
{
    int i;

    data->nr_paths = 0;
    data->nr_colors = 0;
    data->map_rows = 0;
    data->map_colums = 0;
    data->player = 0;
    data->map_start = 0;
    data->map_lenght = 0;
    data->map_row_lenght = 0;

    data->paths = malloc(sizeof(char ***) * 5);
    if (!data->paths)
    {
        printf("malloc failure\n");
        exit(1);
    }
    data->paths[4] = NULL;
    i = 0;
    while (i < 4)
    {
        data->paths[i] = malloc(sizeof(char **) * 3);
        if (!data->paths[i])
        {
            printf("malloc failure\n");
            exit(1);
        }
        data->paths[i][0] = malloc(sizeof(char *) * 1);
        data->paths[i][1] = malloc(sizeof(char *) * 1);

        data->paths[i][2] = NULL;
        i++;
    }

    data->colors = malloc(sizeof(unsigned char ***) * 3);
    if (!data->colors)
    {
        printf("malloc failure\n");
        exit(1);
    }
    data->colors[2] = NULL;
    i = 0;
    while (i < 2)
    {
        data->colors[i] = malloc(sizeof(unsigned char **) * 5);
        if (!data->colors[i])
        {
            printf("malloc failure\n");
            exit(1);
        }
        data->colors[i][0] = malloc(sizeof(unsigned char *) * 1);
        data->colors[i][1] = malloc(sizeof(unsigned char *) * 1);
        data->colors[i][2] = malloc(sizeof(unsigned char *) * 1);
        data->colors[i][3] = malloc(sizeof(unsigned char *) * 1);

        data->colors[i][4] = NULL;
        i++;
    }
}

int check_extension(char *str)
{
    int i;

    i = 0;
    while (str[i] != '.')
        i++;
    if (str[i] == '.')
        i++;
    if (str[i] != 'c' || str[i + 1] != 'u' || str[i + 2] != 'b')
    {
        printf("wrong extension\n");
        return (1);
    }
    return (0);    
}

int main(int argc, char** argv)
{
    t_data data;
    // int fd;

    // fd = open_fd(argv[1]);
    // printf("fd: %d\n", fd);

    if (argc == 2)
    {
        if (check_extension(argv[1]) == 1)
            return (1);
        initialize_data(&data);
        check_input(argv[1], &data);
        printf("test\n");
        // parse_map(fd, &data);
    }
    else
    {
        printf("Wrong number of argumnets\n");
        return (1);
    }

    return (0);
}