#include "MLX42/MLX42.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[])
{
	mlx_t	*mlx; //pointer to mlx instance
	mlx_image_t* imagebuf;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);//create the window and set resize to true
	imagebuf = mlx_new_image(mlx, WIDTH, HEIGHT); //create an image buffer
	if (!mlx)
		exit(EXIT_FAILURE);
	mlx_image_to_window(mlx, imagebuf, 0, 0); //pushing buffer to window starting coordinates 0, 0
	mlx_put_pixel(imagebuf, 100, 100, 0xFFFFFFFF);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}