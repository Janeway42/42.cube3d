/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:08:13 by cpopa         #+#    #+#                 */
/*   Updated: 2022/11/11 17:08:14 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/initialize.h"

void	error_exit_input(char *str)
{
	printf("Error\n");
	printf("%s", str);
	printf("\n");
	exit(1);
}
