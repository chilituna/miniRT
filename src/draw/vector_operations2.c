/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:03:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/10 17:15:37 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


// cross priduct of two vectors
// needed to calculate the right and up vectors
t_vector	ft_cross(t_vector *a, t_vector *b)
{
	t_vector	cross;

	cross.x = a->y * b->z - a->z * b->y;
	cross.y = a->z * b->x - a->x * b->z;
	cross.z = a->x * b->y - a->y * b->x;
	return (cross);
}

// Function to compute the dot product of two vectors
float	ft_dot(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

// Function to compute the perpendicular component of a vector
t_vector	ft_perpendicular(t_vector *a, t_vector *b)
{
	t_vector	perp;
	float		dot;
	t_vector	scaled;

	dot = ft_dot(a, b);
	scaled = ft_scale(b, dot);
	perp = ft_subtract(a, &scaled);
	return (perp);
}
