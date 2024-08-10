/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:15:29 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/10 17:53:08 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Function to calculate the closest hit of the cylinder:
// t1 = (-b - sqrt(discriminant)) / (2.0f * a);
// t2 = (-b + sqrt(discriminant)) / (2.0f * a);
float	ft_closest_hit_cylinder(t_cylinder *cyl, t_ray ray, float t)
{
	float		t1;
	float		t2;
	t_vector	oc;
	float		a;
	float		b;

	oc = ft_subtract(&cyl->origin, &ray.origin);
	a = ft_dot(&ray.direction, &ray.direction);
	b = -2.0 * ft_dot(&ray.direction, &oc);
	t1 = (-b - sqrt(t)) / (2.0f * a);
	t2 = (-b + sqrt(t)) / (2.0f * a);
	if (t1 > 0 && (t1 < t2))
		return (t1);
	if (t2 > 0)
		return (t2);
	return (INFINITY);

}

// Determine if the ray intersects the cylinder:
// 1. intersection with the cylindrical surface:
// 		- check is the ray intersects the infinite cylinder
// 		- check if the hit is within the cylinder height
// 2. intersection with the cylinder caps:
// 		- if the rey does not intersect the infinite cylinder:
//		-- check if it intersects the caps

// 1: intersection with the cylindrical surface
// oc = ray origin to cylinder center
// compute the perpendicular component of the ray direction
// compute the perpendicular component of the oc vector
// solve the quadratic equation: a*t^2 + b*t + c = 0
// where a = perp_dir * perp_dir
// b = 2 * perp_dir * perp_oc
// c = perp_oc * perp_oc - cylinder->diameter / 2 * cylinder->diameter / 2
// if the discriminant is negative, there is no intersection
// if the discriminant is positive, there are two solutions
// if the discriminant is zero, there is one solution
// for each solution, check if the hit is within the cylinder height
// if the hit is within the height, return the hit distance

// 2: intersection with the cylinder caps

float	ft_inter_c(t_cylinder *cylinder, t_ray ray)
{
	t_vector	oc;
	t_vector	perp_dir;
	t_vector	perp_oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = ft_subtract(&ray.origin, &cylinder->origin);
	perp_dir = ft_perpendicular(&ray.direction, &cylinder->orientation);
	perp_oc = ft_perpendicular(&oc, &cylinder->orientation);
	a = ft_dot(&perp_dir, &perp_dir);
	b = 2.0 * ft_dot(&perp_dir, &perp_oc);
	c = ft_dot(&perp_oc, &perp_oc) - (cylinder->diameter / 2.0f)
		* (cylinder->diameter / 2.0f);
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0)
	{
		if (ft_check_height(cylinder, ray, a, b, c, discriminant))
			return (ft_closest_hit_cylinder(cylinder, ray, discriminant));
	}
	else
	{
		if (ft_inter_cap(cylinder, ray))
			return (ft_closest_hit_cylinder(cylinder, ray, discriminant));
	}
	return (-1);
}

void	ft_find_closest_c(t_cylinder *cylinder, t_ray ray, t_hit *hit, float t)
{
	float		hit_distance;
	t_vector	scaled_direction;

	while (cylinder)
	{
		hit_distance = ft_inter_c(cylinder, ray);
		if (hit_distance >= 0)
		{
			hit_distance = ft_closest_hit_cylinder(cylinder, ray, hit_distance);
			if (hit_distance < t)
			{
				t = hit_distance;
				hit->cylinder = cylinder;
				hit->distance = hit_distance;
				scaled_direction = ft_scale(&ray.direction, t);
				hit->hitpoint = ft_add(&ray.origin, &scaled_direction);
				hit->normal = ft_subtract(&hit->hitpoint,
						&hit->cylinder->origin);
				hit->normal = ft_normalize(&hit->normal);
				hit->plane = NULL;
			}
		}
		cylinder = cylinder->next;
	}
}

// draw sphere
t_hit	ft_hit_cylinder(t_data *data, t_ray ray)
{
	float		closest_t;
	t_cylinder	*cylinder;
	t_hit		hit_result;

	closest_t = INFINITY;
	hit_result.distance = INFINITY;
	hit_result.sphere = NULL;
	cylinder = data->cylinder;
	ft_find_closest_c(cylinder, ray, &hit_result, closest_t);
	return (hit_result);
}