/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:57:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/09 15:22:31 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Plane Equation: n * (p - c) = 0
// where n is the normal vector of the plane,
// p is any point on the plane
// c is the known point on the plane
// t = (-n * (ray.origin - c)) / (n * ray.direction)
float	ft_intersection(t_plane *plane, t_ray ray)
{
	t_vector	a;
	t_vector	b;
	float		c;
	float		d;

	a = ft_subtract(&ray.origin, &plane->origin);
	b = ft_scale(&plane->normal, -1);
	c = ft_dot(&a, &b);
	d = ft_dot(&plane->normal, &ray.direction);
	return (c / d);
}

void	ft_find_closest_p(t_plane *plane, t_ray ray, t_hit *hit, float t)
{
	float		hit_distance;
	t_vector	scaled_direction;

	while (plane)
	{
		hit_distance = ft_intersection(plane, ray);
		if (hit_distance >= 0)
		{
			if (hit_distance < t)
			{
				t = hit_distance;
				hit->plane = plane;
				hit->distance = hit_distance;
				scaled_direction = ft_scale(&ray.direction, t);
				hit->hitpoint = ft_add(&ray.origin, &scaled_direction);
				hit->normal = ft_subtract(&hit->hitpoint,
						&hit->plane->origin);
				hit->normal = ft_normalize(&hit->normal);
				hit->sphere = NULL;
			}
		}
		plane = plane->next;
	}
}

// draw plane
t_hit	ft_hit_plane(t_data *data, t_ray ray)
{
	float		closest_t;
	t_plane		*plane;
	t_hit		hit_result;

	closest_t = INFINITY;
	hit_result.distance = INFINITY;
	hit_result.sphere = NULL;
	plane = data->plane;
	ft_find_closest_p(plane, ray, &hit_result, closest_t);
	return (hit_result);
}
