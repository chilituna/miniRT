/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:00:50 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/11 11:24:20 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_vector_length(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
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
