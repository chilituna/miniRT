/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:12:55 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/02 14:51:03 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Set the cylinder values
void	ft_set_cylinder(t_cylinder *cyl, char **pos, char **vec, char **rgb)
{
	cyl->origin->x = ft_atof(pos[0]);
	cyl->origin->y = ft_atof(pos[1]);
	cyl->origin->z = ft_atof(pos[2]);
	cyl->orientation->x = ft_atof(vec[0]);
	cyl->orientation->y = ft_atof(vec[1]);
	cyl->orientation->z = ft_atof(vec[2]);
	cyl->color->r = ft_atoi(rgb[0]);
	cyl->color->g = ft_atoi(rgb[1]);
	cyl->color->b = ft_atoi(rgb[2]);
	ft_free_array(pos);
	ft_free_array(vec);
	ft_free_array(rgb);
}

void	ft_set_cylinder_2(t_cylinder *cylinder, char **arr)
{
	cylinder->diameter = ft_atof(arr[3]);
	cylinder->height = ft_atof(arr[4]);
	ft_free_array(arr);
}
