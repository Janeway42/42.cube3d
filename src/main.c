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
    data->map_start = 0;
}

int main(int argc, char** argv)
{
    t_data data;

    if (argc == 2)
    {
        initialize_data(data);
        check_input(open_fd(argv[1]), data);
        parse_map(open_fd(argv[1]), data);


    }
    else
    {
        printf("Wrong number of argumnets\n");
        return (1);
    }

    return (0);
}