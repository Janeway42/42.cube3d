/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bres_algo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:33:41 by hman          #+#    #+#                 */
/*   Updated: 2022/11/08 12:36:53 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

/*
**	this function will implement the bresenham algorithm for drawing a line
**	source used: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*/

void	draw_line(t_coor point1, t_coor point2, mlx_image_t *img
	, unsigned int colour)
{
	if (abs_int(point2.y - point1.y) < abs_int(point2.x - point1.x))
	{
		if (point1.x > point2.x)
			draw_line_low_slope(point2, point1, img, colour);
		else
			draw_line_low_slope(point1, point2, img, colour);
	}
	else
	{
		if (point1.y > point2.y)
			draw_line_high_slope(point2, point1, img, colour);
		else
			draw_line_high_slope(point1, point2, img, colour);
	}
}

/*
**	this function will draw the line according to the bresenham line algorithm
**	where the slope is between 0 and 1
*/

void	draw_line_low_slope(t_coor point1, t_coor point2, mlx_image_t *img
	, unsigned int colour)
{
	int	dx;
	int	dy;
	int	yi;
	int	difference;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	yi = 1;
	if (dy < 0)
		yi = -1;
	if (dy < 0)
		dy = -dy;
	difference = (2 * dy) - dx;
	while (point1.x <= point2.x)
	{
		draw_pixel(img, point1.x, point1.y, colour);
		if (difference > 0)
		{
			point1.y = point1.y + yi;
			difference = difference + (2 * (dy - dx));
		}
		else
			difference = difference + (2 * dy);
		point1.x = point1.x + 1;
	}
}

void	draw_line_high_slope(t_coor point1, t_coor point2, mlx_image_t *img
	, unsigned int colour)
{
	int	dy;
	int	dx;
	int	xi;
	int	difference;

	dy = point2.y - point1.y;
	dx = point2.x - point1.x;
	xi = 1;
	if (dx < 0)
		xi = -1;
	if (dx < 0)
		dx = -dx;
	difference = (2 * dx) - dy;
	while (point1.y <= point2.y)
	{
		draw_pixel(img, point1.x, point1.y, colour);
		if (difference > 0)
		{
			point1.x = point1.x + xi;
			difference = difference + (2 * (dx - dy));
		}
		else
			difference = difference + (2 * dx);
		point1.y = point1.y + 1;
	}
}

/*
**	this function will retun the absolute number of the integer
**	Word of caution it assumes the number is within the range of an integer
*/
long	abs_int(int number)
{
	if (number >= 0)
		return ((long) number);
	else
		return ((long) -1 * number);
}
