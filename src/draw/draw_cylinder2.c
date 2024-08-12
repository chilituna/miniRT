/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_caps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:41:23 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/12 17:26:49 by aarponen         ###   ########.fr       */
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
float	ft_inter_cap(t_cylinder *cylinder, t_ray ray, float comp_t, t_hit *hit)
{
	t_vector	scaled_direction;
	t_vector	cap_center_bottom;
	t_vector	cap_center_top;
	float		closest_t;
	float		t;

	closest_t = INFINITY;
	scaled_direction = ft_scale(&cylinder->orientation,
			(cylinder->height / 2.0f));
	cap_center_bottom = ft_subtract(&cylinder->origin, &scaled_direction);
	cap_center_top = ft_add(&cylinder->origin, &scaled_direction);
	t = ft_hit_cap(cylinder, ray, cap_center_bottom);
	if (t != INFINITY)
		closest_t = t;
	t = ft_hit_cap(cylinder, ray, cap_center_top);
	if (t != INFINITY && t < closest_t)
		closest_t = t;
	if (closest_t < comp_t)
		hit->cylinder_cap = 1;
	return (closest_t);
}

// calculate the intersection with infinite cylinder
// check if the hit is within the cylinder height
int	ft_check_height(t_cylinder *cylinder, t_ray ray, float t)
{
	t_vector	hitpoint;
	float		projected_height;
	t_vector	scaled_direction;
	t_vector	subtracted;

	scaled_direction = ft_scale(&ray.direction, t);
	hitpoint = ft_add(&ray.origin, &scaled_direction);
	subtracted = ft_subtract(&hitpoint, &cylinder->origin);
	projected_height = ft_dot(&subtracted, &cylinder->orientation);
	if (projected_height >= -cylinder->height / 2.0f && projected_height
		<= cylinder->height / 2.0f)
		return (1);
	return (0);
}

// calculate the normal vector of the hit point
void	ft_calculate_normal_c(t_cylinder *cylinder, t_hit *hit)
{
	t_vector	projection;
	t_vector	hit_to_origin;

	if (hit->cylinder_cap)
	{
		hit->normal = cylinder->orientation;
		return ;
	}
	hit_to_origin = ft_subtract(&hit->hitpoint, &cylinder->origin);
	projection = ft_scale(&cylinder->orientation, ft_dot(&hit_to_origin,
				&cylinder->orientation));
	hit->normal = ft_subtract(&hit_to_origin, &projection);
	hit->normal = ft_normalize(&hit->normal);
}
