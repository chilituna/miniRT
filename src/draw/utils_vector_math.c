/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector_math.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:03:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/02 14:53:00 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Function to compute the dot product of two vectors
float	ft_dot(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

// Function to subtract two vectors
t_vector	ft_subtract(t_vector *a, t_vector *b)
{
	t_vector	result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

// Function to add two vectors
t_vector	ft_add(t_vector *a, t_vector *b)
{
	t_vector	result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

// Function to scale a vector
t_vector	ft_scale(t_vector *a, float scale)
{
	t_vector	result;

	result.x = a->x * scale;
	result.y = a->y * scale;
	result.z = a->z * scale;
	return (result);
}

// Normalize a vector: unit vector has a length of 1
t_vector	ft_normalize(t_vector *a)
{
	t_vector	result;
	float		length;

	length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	result.x = a->x / length;
	result.y = a->y / length;
	result.z = a->z / length;
	return (result);
}
