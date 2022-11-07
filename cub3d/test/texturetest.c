#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#define WIDTH 1000 
#define HEIGHT 1000

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	draw_pixel(mlx_image_t *img, unsigned int x, unsigned int y
			, unsigned int colour)
{
	unsigned char	*dst;
	unsigned int	offset;

	if (x < img->width && y < img->height)
	{
		offset = y * (img->width * 4) + x * 4;
		dst = img->pixels + offset;
		*(unsigned int *)dst = colour;
	}
}

unsigned int getColourPNG(mlx_texture_t* png, unsigned int x, unsigned y)
{
	unsigned int offset;
	unsigned char	*dst;

	if(x < png->width && y < png->height)
	{
		offset = y * (png->width * 4) + x * 4;
		dst = png->pixels + offset;
		return (*(unsigned int*) dst);
	}
	return (0X00000000);
}


int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Try to load the file
	xpm_t* xpm = mlx_load_xpm42("brick.xpm42");
	if (!xpm)
        error();
	
	mlx_texture_t* png = mlx_load_png("brick.png"); // it will return NULL when the file given is not a png file
	if (png == NULL)
	{
		return (1);
	}

	mlx_image_t* img = mlx_new_image(mlx, 1000, 1000);

	for(int x = 0; x < png->width; ++x)
	{
		for(int y = 0; y < png->height; ++y)
		{
			if (x % 10 < 5)
			{
				draw_pixel(img, x, y, getColourPNG(png, x, y));
			}
			else
				draw_pixel(img, x, y, 0XFF000000);
		}
	}


	//mlx_image_t* img = mlx_texture_to_image(mlx, png);

	// Convert texture to a displayable image
//	mlx_image_t* img = mlx_texture_to_image(mlx, &xpm->texture);
//	if (!img)
//        error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any left overs, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_xpm42(xpm);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}