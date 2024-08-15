/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:15:29 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/12 17:26:39 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

float	*ft_discriminant_c(t_cylinder *cylinder, t_ray ray)
{
	t_vector	perp_dir;
	t_vector	perp_oc;
	float		*calc;

	calc = (float *)malloc(sizeof(float) * 4);
	if (!calc)
		return (NULL);
	perp_dir = ft_perpendicular(&ray.direction, &cylinder->orientation);
	perp_oc = ft_subtract(&ray.origin, &cylinder->origin);
	perp_oc = ft_perpendicular(&perp_oc, &cylinder->orientation);
	calc[0] = ft_dot(&perp_dir, &perp_dir);
	calc[1] = 2.0 * ft_dot(&perp_dir, &perp_oc);
	calc[2] = ft_dot(&perp_oc, &perp_oc) - (cylinder->diameter / 2.0f)
		* (cylinder->diameter / 2.0f);
	calc[3] = calc[1] * calc[1] - 4.0f * calc[0] * calc[2];
	return (calc);
}

// calc = {a, b, c, discriminant}
float	ft_inter_c(t_cylinder *cylinder, t_ray ray, t_data *data, t_hit *hit)
{
	float		*calc;
	float		t1;
	float		t2;
	float		t3;
	float		closest_t;

	closest_t = INFINITY;
	calc = ft_discriminant_c(cylinder, ray);
	if (!calc)
		ft_error("Malloc failed", data);
	if (calc[3] >= 0)
	{
		t1 = (-calc[1] - sqrt(calc[3])) / (2.0f * calc[0]);
		t2 = (-calc[1] + sqrt(calc[3])) / (2.0f * calc[0]);
		if (t1 > 0 && ft_check_height(cylinder, ray, t1))
			closest_t = t1;
		if (t2 > 0 && ft_check_height(cylinder, ray, t2) && t2 < closest_t)
			closest_t = t2;
	}
	t3 = ft_inter_cap(cylinder, ray, closest_t, hit);
	if (t3 < closest_t)
		closest_t = t3;
	free(calc);
	return (closest_t);
}

void	ft_find_closest_c(t_data *data, t_ray ray, t_hit *hit, float t)
{
	t_cylinder	*cylinder;
	float		hit_distance;
	t_vector	scaled_direction;

	cylinder = data->cylinder;
	while (cylinder)
	{
		cylinder->orientation = ft_normalize(&cylinder->orientation);
		hit_distance = ft_inter_c(cylinder, ray, data, hit);
		if (hit_distance < t)
		{
			t = hit_distance;
			hit->cylinder = cylinder;
			hit->distance = hit_distance;
			scaled_direction = ft_scale(&ray.direction, t);
			hit->hitpoint = ft_add(&ray.origin, &scaled_direction);
			ft_calculate_normal_c(cylinder, hit);
			hit->sphere = NULL;
			hit->plane = NULL;
		}
		cylinder = cylinder->next;
	}
}

// draw sphere
t_hit	ft_hit_cylinder(t_data *data, t_ray ray)
{
	float		closest_t;
	t_hit		hit_result;

	closest_t = INFINITY;
	hit_result.distance = INFINITY;
	hit_result.sphere = NULL;
	hit_result.plane = NULL;
	hit_result.cylinder_cap = 0;
	ft_find_closest_c(data, ray, &hit_result, closest_t);
	return (hit_result);
}
