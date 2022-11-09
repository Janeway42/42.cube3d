#include <stdio.h>
unsigned char get_colour_value(unsigned int colour,char colourpart)
{
	if(colourpart == 'R')
		return ((unsigned char)(colour & 0x000000FF));
	else if (colourpart == 'G')
		return ((unsigned char)((colour & 0x0000FF00)>>8));
	else if (colourpart == 'B')
		return ((unsigned char)((colour & 0x00FF0000)>>16));
	return (0);
}
unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b
				, unsigned char a)
{
	return ((unsigned int)(a << 24 | b << 16 | g << 8 | r));
}

int main()
{
    unsigned int colour = create_colour(220,27,120,255);
   printf("R : %d, G: %d B : %d\n", get_colour_value(colour, 'R'), get_colour_value(colour,'G'),get_colour_value(colour,'B'));

}