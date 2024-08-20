/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sveselov <sveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:50:06 by sveselov          #+#    #+#             */
/*   Updated: 2024/08/20 18:12:48 by sveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	ft_get_light_dir(t_data *data, t_hit hit)
{
	t_vector	diff;

	diff = ft_subtract(&data->light->origin, &hit.hitpoint);
	return (ft_normalize(&diff));
}

t_vector	ft_get_view_dir(t_data *data, t_hit hit)
{
	t_vector	view_dir;

	view_dir = ft_subtract(&data->camera->origin, &hit.hitpoint);
	return (ft_normalize(&view_dir));
}

float	ft_get_light_intensity(t_data *data, t_hit hit,
	t_vector light_dir, t_vector view_dir)
{
	float	diffuse;
	float	specular;

	diffuse = 0.0f;
	specular = 0.0f;
	if (!ft_is_in_shadow(data, &hit.hitpoint, &hit.normal, &light_dir))
	{
		diffuse = ft_calculate_diffuse_lighting(&hit.normal, &light_dir);
		specular = ft_calculate_specular_lighting(&view_dir, &light_dir,
				&hit.normal, 1.0f);
	}
	return (diffuse + specular);
}

t_color	ft_calculate_lighting(t_data *data, t_hit hit)
{
	t_vector	light_dir;
	t_vector	view_dir;
	float		light_intensity;
	t_color		ambient_color;
	t_color		final_color;

	light_dir = ft_get_light_dir(data, hit);
	view_dir = ft_get_view_dir(data, hit);
	ft_calculate_ambient_lighting(data, &ambient_color);
	light_intensity = ft_get_light_intensity(data, hit, light_dir, view_dir);
	final_color = ft_get_object_color(hit, light_intensity, ambient_color);
	ft_clamp_color(&final_color);
	return (final_color);
}
