/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_buffer_functions.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:07:39 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/11 17:07:40 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

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
