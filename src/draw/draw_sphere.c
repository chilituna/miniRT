/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:05:52 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/04 21:49:45 by s0nia            ###   ########.fr       */
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

// t_hit	ft_set_hit_result(t_hit hit, float t, t_sphere *sphere, t_ray ray)
// {
// 	t_vector	scaled_direction;

// 	scaled_direction = ft_scale(&ray.direction, t);
// 	hit.sphere = sphere;
// 	hit.distance = t;
// 	hit.hitpoint = ft_add(&ray.origin, &scaled_direction);
// 	hit.normal = ft_subtract(&hit.hitpoint,
// 			&hit.sphere->origin);
// 	return (hit);
// }

float	ft_find_closest(t_sphere *sphere, t_ray ray, t_hit *hit, float t)
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
			}
		}
		sphere = sphere->next;
	}
	return (t);
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
	closest_t = ft_find_closest(sphere, ray, &hit_result, closest_t);
	return (hit_result);
}
