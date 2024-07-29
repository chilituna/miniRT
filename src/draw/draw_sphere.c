/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:05:52 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/29 13:04:04 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"



// Function to calculate the ray direction
// Normalized Device Coordinates (NDC) centers the rays in the middle of
// each pixel.
// Map NDC to screen space: accounts for aspect ratio and FOV
// Normalize the direction vector: Ensuring the vector has a unit length
t_vector	ft_calc_ray_direction(t_data *data, int x, int y)
{
	float		aspect_ratio;
	float		viewport_height;
	float		viewport_width;
	float		focal_length;
	t_vector	direction;

	(void)data;
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	viewport_height = 2.0f;
	viewport_width = aspect_ratio * viewport_height;
	focal_length = 1.0f;
	direction.x = viewport_width * ((float)x / (float)WIDTH - 0.5f);
	direction.y = viewport_height * ((float)y / (float)HEIGHT - 0.5f);
	direction.z = -focal_length;
	direction = ft_normalize(&direction);
	return (direction);
}

// draw sphere
// (bx^2 + by^2 + bz^2)t^2 + 2(axbx + ayby azbz)t +
// (ax^2 + ay^2 + az^2 - r^2) = 0
// where
// a = ray origin = camera position
// b = ray direction
// r = radius = sphere radius
// t = hit distance
//
float	ft_hit_sphere(t_data *data, int x, int y)
{
	t_ray		ray;
	t_vector	oc; // vector from ray origin to sphere center
	float		a;
	float		b;
	float		c;
	float		discriminant;

	ray.origin = *data->camera->origin;
	ray.direction = ft_calc_ray_direction(data, x, y);
	a = ft_dot(&ray.direction, &ray.direction);
	b = 2.0 * ft_dot(&oc, &ray.direction);
	c = ft_dot(&ray.origin, &ray.origin) - (data->sphere->diameter / 2)
		* (data->sphere->diameter / 2);
	discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0)
		return (-1.0f);
	else
		return (1.0f);
}
