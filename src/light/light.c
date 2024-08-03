/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:23:55 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/04 00:28:04 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float calculate_diffuse_light(t_vector normal, t_vector light_dir) {
	float dot_product = ft_dot(&normal, &light_dir);
	return fmaxf(dot_product, 0.0f);
}

t_color	calculate_lighting(t_hit hit, t_data *data)
{
	t_color final_color = {0, 0, 0};
	t_light_info light_info;
	t_vector light_dir;
	float diffuse_intensity;
	
	// Ambient lighting
	final_color.r += data->ambient->ratio * data->ambient->color->r * hit.sphere->color->r / 255.0f;
	final_color.g += data->ambient->ratio * data->ambient->color->g * hit.sphere->color->g / 255.0f;
	final_color.b += data->ambient->ratio * data->ambient->color->b * hit.sphere->color->b / 255.0f;

	// Diffuse lighting
	light_dir = ft_subtract(data->light->origin, &hit.hitpoint);
	light_info.light_distance = sqrt(ft_dot(&light_dir, &light_dir));
	light_info.light_dir = ft_normalize(&light_dir);
	
	// Check for shadows
	t_ray shadow_ray;
	shadow_ray.origin = hit.hitpoint;
	shadow_ray.direction = light_info.light_dir;
	t_hit shadow_hit = ft_hit_sphere(data, shadow_ray);
	
	if (shadow_hit.distance < light_info.light_distance) {
		// Point is in shadow
		return final_color;
	}

	diffuse_intensity = calculate_diffuse_light(hit.normal, light_info.light_dir);
	light_info.intensity = data->light->ratio * diffuse_intensity;

	final_color.r += light_info.intensity * hit.sphere->color->r;
	final_color.g += light_info.intensity * hit.sphere->color->g;
	final_color.b += light_info.intensity * hit.sphere->color->b;

	// Clamp colors to [0, 255]
	final_color.r = fminf(final_color.r, 255);
	final_color.g = fminf(final_color.g, 255);
	final_color.b = fminf(final_color.b, 255);

	return final_color;
}
