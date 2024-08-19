/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:04:27 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/16 23:10:24 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_calculate_diffuse_lighting(t_vector *normal, t_vector *light_dir)
{
	float	dot_product;

	dot_product = ft_dot(normal, light_dir);
	return (fmaxf(0.0f, dot_product));
}

void	ft_calculate_ambient_lighting(t_data *data, t_color *color)
{
	float	ambient_ratio;

	ambient_ratio = data->ambient->ratio;
	color->r += (int)(data->ambient->color.r * ambient_ratio);
	color->g += (int)(data->ambient->color.g * ambient_ratio);
	color->b += (int)(data->ambient->color.b * ambient_ratio);
}

float	ft_calculate_specular_lighting(t_vector *view_dir, t_vector *light_dir,
		t_vector *normal, float shininess)
{
	t_vector	scaled;
	t_vector	reflect_dir;
	float		spec;

	scaled = ft_scale(normal, 2.0f * ft_dot(light_dir, normal));
	reflect_dir = ft_subtract(light_dir, &scaled);
	spec = powf(fmaxf(ft_dot(view_dir, &reflect_dir), 0.0f), shininess);
	return (spec);
}

static t_hit	ft_min_hit(t_hit hit1, t_hit hit2)
{
	if (hit1.distance < hit2.distance)
		return (hit1);
	return (hit2);
}

int	ft_is_in_shadow(t_data *data, t_vector *hit_point,
			t_vector *normal, t_vector *light_dir)
{
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_vector	light_vector;
	float		light_distance;
	t_vector	offset;

	offset = ft_scale(normal, 0.001f);
	shadow_ray.origin = ft_add(hit_point, &offset);
	shadow_ray.direction = *light_dir;
	shadow_hit.distance = INFINITY;
	if (data->sphere)
		shadow_hit = ft_min_hit(shadow_hit, ft_hit_sphere(data, shadow_ray));
	if (data->plane)
		shadow_hit = ft_min_hit(shadow_hit, ft_hit_plane(data, shadow_ray));
	if (data->cylinder)
		shadow_hit = ft_min_hit(shadow_hit, ft_hit_cylinder(data, shadow_ray));
	light_vector = ft_subtract(&data->light->origin, hit_point);
	light_distance = ft_vector_length(&light_vector);
	return (shadow_hit.distance > 0.001f
		&& shadow_hit.distance < light_distance);
}
