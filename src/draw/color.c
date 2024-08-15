/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:08:16 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/10 17:38:11 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Calculate the color and put it to image:
// just to test out, calculate color based on the xyz hitpoint
// void	ft_put_color(t_data *data, int x, int y, t_hit hit)
// {
// 	t_vector	diff = ft_subtract(&data->light->origin, &hit.hitpoint);
// 	t_vector	light_dir = ft_normalize(&diff);
// 	float		diffuse =
//ft_calculate_diffuse_lighting(&hit.normal, &light_dir);
// 	t_color final_color;

// 	printf("diffuse: %f\n", diffuse);
// 	final_color.r = (int)(hit.sphere->color.r * diffuse);
// 	final_color.g = (int)(hit.sphere->color.g * diffuse);
// 	final_color.b = (int)(hit.sphere->color.b * diffuse);

// 	ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(1, &final_color));
// }

t_color	ft_sphere_color(t_hit hit, float diffuse, t_color ambient_color)
{
	t_color	final_color;

	final_color.r = (int)(hit.sphere->color.r
			* (diffuse + ambient_color.r / 255.0f));
	final_color.g = (int)(hit.sphere->color.g
			* (diffuse + ambient_color.g / 255.0f));
	final_color.b = (int)(hit.sphere->color.b
			* (diffuse + ambient_color.b / 255.0f));
	return (final_color);
}

t_color	ft_plane_color(t_hit hit, float diffuse, t_color ambient_color)
{
	t_color	final_color;

	final_color.r = (int)(hit.plane->color.r
			* (diffuse + ambient_color.r / 255.0f));
	final_color.g = (int)(hit.plane->color.g
			* (diffuse + ambient_color.g / 255.0f));
	final_color.b = (int)(hit.plane->color.b
			* (diffuse + ambient_color.b / 255.0f));
	return (final_color);
}

t_color	ft_cylinder_color(t_hit hit, float diffuse, t_color ambient_color)
{
	t_color	final_color;

	final_color.r = (int)(hit.cylinder->color.r
			* (diffuse + ambient_color.r / 255.0f));
	final_color.g = (int)(hit.cylinder->color.g
			* (diffuse + ambient_color.g / 255.0f));
	final_color.b = (int)(hit.cylinder->color.b
			* (diffuse + ambient_color.b / 255.0f));
	return (final_color);
}

void	ft_put_color(t_data *data, int x, int y, t_hit hit)
{
	t_vector	diff;
	t_vector	light_dir;
	float		diffuse;
	t_color		ambient_color;
	t_color		final_color;

	diff = ft_subtract(&data->light->origin, &hit.hitpoint);
	light_dir = ft_normalize(&diff);
	diffuse = 0.0f;
	ambient_color = (t_color){0, 0, 0};
	ft_calculate_ambient_lighting(data, &ambient_color);
	if (!ft_is_in_shadow(data, &hit.hitpoint, &light_dir))
		diffuse = ft_calculate_diffuse_lighting(&hit.normal, &light_dir);
	if (hit.sphere)
		final_color = ft_sphere_color(hit, diffuse, ambient_color);
	else if (hit.plane)
		final_color = ft_plane_color(hit, diffuse, ambient_color);
	else if (hit.cylinder)
		final_color = ft_cylinder_color(hit, diffuse, ambient_color);
	final_color.r = fminf(final_color.r, 255);
	final_color.g = fminf(final_color.g, 255);
	final_color.b = fminf(final_color.b, 255);
	ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(1, &final_color));
}
