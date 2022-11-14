/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:07:29 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/14 16:24:23 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

//function will change the given colour to a darker tone depending on the 
//percentage it is given.
unsigned int	grading_colour(unsigned int colour, double percentage)
{
	t_rgba	color;

	color.rgba = colour;
	if (percentage < 1.0)
	{
		color.r = (unsigned char)((percentage) * color.r);
		color.g = (unsigned char)((percentage) * color.g);
		color.b = (unsigned char)((percentage) * color.b);
	}
	return (color.rgba);
}

//will get the colour on a specific point on the texture
unsigned int	get_colour_png(mlx_texture_t *png, unsigned int x
					, unsigned int y)
{
	unsigned int	offset;
	unsigned char	*dst;

	if (x < png->width && y < png->height)
	{
		offset = y * (png->width * 4) + x * 4;
		dst = png->pixels + offset;
		return (*(unsigned int *) dst);
	}
	return (0XFF000000);
}

//since MLX42 uses the RGBA format the color need to be created as such
//but mlx42 is also little endian so it will be ARGB.
unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b
				, unsigned char a)
{
	return ((unsigned int)(a << 24 | b << 16 | g << 8 | r));
}
