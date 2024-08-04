/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:00:50 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/04 21:04:18 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	calculate_eye_vector(t_vector intersection_point, t_vector ray_origin)
{
	t_vector eye_vector;

	eye_vector.x = ray_origin.x - intersection_point.x;
	eye_vector.y = ray_origin.y - intersection_point.y;
	eye_vector.z = ray_origin.z - intersection_point.z;
	return ft_normalize(&eye_vector);
}

t_vector	calculate_light_vector(t_vector intersection_point, t_vector light_position)
{
	t_vector light_vector;

	light_vector.x = light_position.x - intersection_point.x;
	light_vector.y = light_position.y - intersection_point.y;
	light_vector.z = light_position.z - intersection_point.z;
	return ft_normalize(&light_vector);
}

t_vector	calculate_normal_vector(t_vector intersection_point, t_sphere sphere)
{
	t_vector normal_vector;

	normal_vector.x = intersection_point.x - sphere.origin.x;
	normal_vector.y = intersection_point.y - sphere.origin.y;
	normal_vector.z = intersection_point.z - sphere.origin.z;
	return ft_normalize(&normal_vector);
}

t_vector	calculate_reflection_vector(t_vector light_vector, t_vector normal_vector)
{
	float dot_product = ft_dot(&light_vector, &normal_vector);
	t_vector reflection_vector;

	reflection_vector.x = 2 * dot_product * normal_vector.x - light_vector.x;
	reflection_vector.y = 2 * dot_product * normal_vector.y - light_vector.y;
	reflection_vector.z = 2 * dot_product * normal_vector.z - light_vector.z;
	return ft_normalize(&reflection_vector);
}
