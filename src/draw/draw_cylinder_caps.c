/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_caps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:41:23 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/11 11:44:19 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// check if the ray hits the cylinder caps
// if so, return the hit distance
// otherwise, return INFINITY
float	ft_hit_cap(t_cylinder *cylinder, t_ray ray, t_vector cap_center)
{
	float		t;
	t_vector	oc;
	t_vector	hitpoint;
	t_vector	scaled_ray;
	float		distance;

	oc = ft_subtract(&cap_center, &ray.origin);
	t = ft_dot(&oc, &cylinder->orientation) / ft_dot(&ray.direction,
			&cylinder->orientation);
	scaled_ray = ft_scale(&ray.direction, t);
	hitpoint = ft_add(&ray.origin, &scaled_ray);
	scaled_ray = ft_subtract(&hitpoint, &cap_center);
	distance = ft_vector_length(&scaled_ray);
	if (distance <= cylinder->diameter / 2.0f)
		return (t);
	return (INFINITY);
}

// calculate the intersection with the cylinder caps:
// calculate the center of the bottom and top caps
// send both caps to the hit_cap function
// if the ray intersects either of the caps, return the hit distance
float	ft_inter_cap(t_cylinder *cylinder, t_ray ray)
{
	float		dist_to_cap;
	t_vector	scaled_direction;
	t_vector	cap_center_bottom;
	t_vector	cap_center_top;
	float		t;

	dist_to_cap = cylinder->height / 2.0f;
	scaled_direction = ft_scale(&cylinder->orientation, dist_to_cap);
	cap_center_bottom = ft_subtract(&cylinder->origin, &scaled_direction);
	cap_center_top = ft_add(&cylinder->origin, &scaled_direction);
	t = ft_hit_cap(cylinder, ray, cap_center_bottom);
	if (t != INFINITY)
		return (t);
	t = ft_hit_cap(cylinder, ray, cap_center_top);
	return (t);
}
