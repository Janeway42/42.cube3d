/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:08:08 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/11 17:08:08 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

//converting the t_vector to t_coor datatype 
//converting the x and y double to int.
t_coor	vec_to_coor(t_vector vec)
{
	t_coor	temp_coor;

	temp_coor.x = (int) vec.x;
	temp_coor.y = (int) vec.y;
	return (temp_coor);
}

t_vector	add_vectors(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vector	subtract_vectors(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	return (result);
}

//this function rotates the vector
//the degree multiplied by negative number because the y coordinates
//on the imagebuffer increment when going down and decrement when going up.

t_vector	rotate_vector(t_vector vec, double degree)
{
	double		radians;
	t_vector	result;

	radians = (-degree / 180.0) * M_PI;
	result.x = vec.x * cos(radians) - vec.y * sin(radians);
	result.y = vec.x * sin(radians) + vec.y * cos(radians);
	return (result);
}
