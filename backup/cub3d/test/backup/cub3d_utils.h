#ifndef CUB3D_UTILS_H
# define CUB3D_UTILS_H

#include "cub3d_struct.h"

t_coor			vec_to_coor(t_vector vec);
unsigned int	create_colour(unsigned char r, unsigned char g, unsigned char b,
					unsigned char a);
t_vector		add_vectors(t_vector vec1, t_vector vec2);
t_vector		subtract_vectors(t_vector vec1, t_vector vec2);
t_vector		rotate_vector(t_vector vect, double degree);

#endif