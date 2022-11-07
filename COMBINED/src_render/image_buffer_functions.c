#include "render.h"

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

//function that will "clear" the image buffer with the black colour.
void	clear_image(mlx_image_t *img)
{
	ft_memset((void *) img->pixels, 0, img->width * img->height * 4);
}
