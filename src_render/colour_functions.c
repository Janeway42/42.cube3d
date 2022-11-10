#include "../includes/render.h"

	// unsigned char	r;
	// unsigned char	g;
	// unsigned char	b;

	// if (percentage < 1.0)
	// {
	// 	r = (unsigned char)(percentage * get_colour_value(colour, 'r'));
	// 	g = (unsigned char)(percentage * get_colour_value(colour, 'g'));
	// 	b = (unsigned char)(percentage * get_colour_value(colour, 'b'));
	// 	return (create_colour(r, g, b, 255));
	// }
	// return (colour);

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

unsigned char	get_colour_value(unsigned int colour, char colourpart)
{
	if (colourpart == 'r')
		return ((unsigned char)(colour & 0x000000FF));
	else if (colourpart == 'g')
		return ((unsigned char)((colour & 0x0000FF00) >> 8));
	else if (colourpart == 'b')
		return ((unsigned char)((colour & 0x00FF0000) >> 16));
	return (0);
}
