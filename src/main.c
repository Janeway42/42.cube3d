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
    data->nr_paths = 0;
    data->nr_colors = 0;
    data->map_rows = 0;
    data->map_colums = 0;
    data->player = 0;
    // data->map_start = 0;
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
    int fd;

    fd = open_fd(argv[1]);
    printf("fd: %d\n", fd);

    if (argc == 2)
    {
        if (check_extension(argv[1]) == 1)
            return (1);
        initialize_data(&data);
        check_input(fd, &data);
        printf("test\n");
        parse_map(fd, &data);
    }
    else
    {
        printf("Wrong number of argumnets\n");
        return (1);
    }

    return (0);
}