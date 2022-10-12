#include "../includes/cube3d.h"

int main(int argc, char** argv)
{
    t_data data;

    if (argc == 2)
    {
        parse_map(argv[1], data);


    }
    else
    {
        printf("Wrong number of argumnets\n");
        return (1);
    }

    return (0);
}