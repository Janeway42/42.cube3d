#include "../includes/cube3d.h"

int open_fd(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        error_exit_input("failed to open fd");
    return (fd);
}

unsigned char **assign_memory(void)
{
    unsigned char **str;
    int i;

    str = malloc(sizeof(char **) * 3);
    if (!str)
        error_exit_input("malloc fail");
    str[2] = NULL;
    i = 0;
    while (i < 2)
    {
        str[i] = malloc(sizeof(char *) * 1);
        if (!str[i])
            error_exit_input("malloc fail");
        str[i][0] = '\0';
        i++;
    }
    return (str);
}

static void initialize_data(t_data *data)
{
    data->nr_paths = 0;
    data->nr_colors = 0;
    data->map_rows = 0;
    data->map_colums = 0;
    data->player = 0;
    data->map_start = 0;
    data->map_lenght = 0;
    data->map_row_lenght = 0;

    data->north = (char **)assign_memory();
    data->south = (char **)assign_memory();
    data->east = (char **)assign_memory();
    data->west = (char **)assign_memory();
    data->floor = assign_memory();
    data->celeing = assign_memory();
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

    if (argc == 2)
    {
        if (check_extension(argv[1]) == 1)
            return (1);
        initialize_data(&data);
        process_input(argv[1], &data);
    }
    else
    {
        printf("Wrong number of argumnets\n");
        return (1);
    }

    return (0);
}