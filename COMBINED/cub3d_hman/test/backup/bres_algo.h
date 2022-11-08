/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bres_algo.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/30 12:25:10 by hman          #+#    #+#                 */
/*   Updated: 2022/10/17 18:24:58 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRES_ALGO_H
# define BRES_ALGO_H

# include "cub3d_struct.h"
# include "MLX42/MLX42.h"

void	draw_line(t_coor point1, t_coor point2, mlx_image_t *img,
			unsigned int colour);
void	draw_line_low_slope(t_coor point1, t_coor point2, mlx_image_t *img,
			unsigned int colour);
void	draw_line_high_slope(t_coor point1, t_coor point2, mlx_image_t *img,
			unsigned int colour);
long	abs_int(int number);

#endif