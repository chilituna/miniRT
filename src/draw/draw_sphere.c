/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:05:52 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/07 16:16:22 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Function to calculate the hit distance of the sphere
// (bx^2 + by^2 + bz^2)t^2 + 2(axbx + ayby azbz)t +
// (ax^2 + ay^2 + az^2 - r^2) = 0
// where
// a = ray origin = camera position
// b = ray direction
// r = radius = sphere radius
// t = hit distance
// oc = origin to center
float	ft_closest_hit_sphere(t_sphere *sphere, t_ray ray, float discriminant)
{
	float		t1;
	float		t2;
	t_vector	oc;
	float		a;
	float		b;

	oc = ft_subtract(&sphere->origin, &ray.origin);
	a = ft_dot(&ray.direction, &ray.direction);
	b = 2.0 * ft_dot(&ray.direction, &oc);
	t1 = (-b - sqrt(discriminant)) / (2.0f * a);
	t2 = (-b + sqrt(discriminant)) / (2.0f * a);
	if (t1 > 0 && (t1 < t2))
		return (t1);
	if (t2 > 0)
		return (t2);
	return (INFINITY);
}

float	ft_discriminant(t_sphere *sphere, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;

	oc = ft_subtract(&sphere->origin, &ray.origin);
	a = ft_dot(&ray.direction, &ray.direction);
	b = 2.0 * ft_dot(&ray.direction, &oc);
	c = ft_dot(&oc, &oc) - (sphere->diameter / 2.0f)
		* (sphere->diameter / 2.0f);
	return (b * b - 4.0f * a * c);
}

void	ft_find_closest(t_sphere *sphere, t_ray ray, t_hit *hit, float t)
{
	float		discriminant;
	float		hit_distance;
	t_vector	scaled_direction;

	while (sphere)
	{
		discriminant = ft_discriminant(sphere, ray);
		if (discriminant >= 0)
		{
			hit_distance = ft_closest_hit_sphere(sphere, ray, discriminant);
			if (hit_distance < t)
			{
				t = hit_distance;
				hit->sphere = sphere;
				hit->distance = hit_distance;
				scaled_direction = ft_scale(&ray.direction, t);
				hit->hitpoint = ft_add(&ray.origin, &scaled_direction);
				hit->normal = ft_subtract(&hit->hitpoint,
						&hit->sphere->origin);
				hit->normal = ft_normalize(&hit->normal);
				// printf("Hit distance: %f\n", hit->distance);
				// printf("ray direction: %f %f %f\n", ray.direction.x,
				// 		hit->hitpoint.y, hit->hitpoint.z);
				// printf("Normal: %f %f %f\n", hit->normal.x,
				// 		hit->normal.y, hit->normal.z);
			}
		}
		sphere = sphere->next;
	}
}

// draw sphere
t_hit	ft_hit_sphere(t_data *data, t_ray ray)
{
	float		closest_t;
	t_sphere	*sphere;
	t_hit		hit_result;

	closest_t = INFINITY;
	hit_result.distance = INFINITY;
	hit_result.sphere = NULL;
	sphere = data->sphere;
	ft_find_closest(sphere, ray, &hit_result, closest_t);
	return (hit_result);
}
