/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:04:27 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/11 11:25:13 by aarponen         ###   ########.fr       */
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

int	ft_is_in_shadow(t_data *data, t_vector *hit_point, t_vector *light_dir)
{
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_vector	light_vector;
	float		light_distance;

	shadow_ray.origin = *hit_point;
	shadow_ray.direction = *light_dir;
	shadow_hit = ft_hit_sphere(data, shadow_ray);
	light_vector = ft_subtract(&data->light->origin, hit_point);
	light_distance = ft_vector_length(&light_vector);
	return (shadow_hit.distance > 0.001f
		&& shadow_hit.distance < light_distance);
}
