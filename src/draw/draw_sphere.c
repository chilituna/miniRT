/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:05:52 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/02 09:34:33 by aarponen         ###   ########.fr       */
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
// oc = origin to center
t_hit	ft_hit_sphere(t_data *data, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t1;
	float		t2;
	float		closest_t;
	t_sphere	*sphere;
	t_sphere	*closest_sphere;
	t_hit 		result;

	closest_t = INFINITY;
	closest_sphere = NULL;
	sphere = data->sphere;
	while (sphere)
	{
		oc = ft_subtract(&ray.origin, sphere->origin);
		a = ft_dot(&ray.direction, &ray.direction);
		b = 2.0 * ft_dot(&oc, &ray.direction);
		c = ft_dot(&oc, &oc) - (sphere->diameter / 2.0f)
			* (sphere->diameter / 2.0f);
		discriminant = b * b - 4.0f * a * c;
		if (discriminant >= 0)
		{
			t1 = (b - sqrt(discriminant)) / (2.0f * a);
			t2 = (b + sqrt(discriminant)) / (2.0f * a);
			if (t1 > 0 && t1 < closest_t)
			{
				closest_t = t1;
				closest_sphere = sphere;
			}
			if (t2 > 0 && t2 < closest_t)
			{
				closest_t = t2;
				closest_sphere = sphere;
			}
		}
		sphere = sphere->next;
	}
	result = (t_hit){closest_t, closest_sphere};
	return (result);
}
