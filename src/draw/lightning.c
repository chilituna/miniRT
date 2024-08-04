/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:42:28 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/04 14:23:13 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	ft_calculate_diffuse(t_hit hit, t_light *light, t_color sphere_color)
{
	t_vector	light_dir;
	float		diffuse_strength;
	float		dot_product;
	t_color		diffuse_color;

	// Calculate direction from hit point to light
	light_dir = ft_subtract(light->origin, &hit.hitpoint);
	light_dir = ft_normalize(&light_dir);

	// Calculate diffuse strength
	printf("Normal: (%.2f, %.2f, %.2f)\n", hit.normal.x, hit.normal.y, hit.normal.z);
	printf("Light direction: (%.2f, %.2f, %.2f)\n", light_dir.x, light_dir.y, light_dir.z);
	dot_product = ft_dot(&hit.normal, &light_dir);
	diffuse_strength = fabs(dot_product);
	printf("Final diffuse strength: %.6f\n", diffuse_strength);

	// Calculate final diffuse color
	diffuse_color.r = (int)(sphere_color.r * diffuse_strength * light->ratio);
	diffuse_color.g = (int)(sphere_color.g * diffuse_strength * light->ratio);
	diffuse_color.b = (int)(sphere_color.b * diffuse_strength * light->ratio);

	printf("Diffuse: Light pos (%.2f, %.2f, %.2f), Strength: %.2f, Color: (%d, %d, %d)\n", 
		   light->origin->x, light->origin->y, light->origin->z,
		   diffuse_strength, diffuse_color.r, diffuse_color.g, diffuse_color.b);

	return (diffuse_color);
}

t_color	ft_add_ambient(t_color color, t_ambient *ambient)
{
	t_color	result;

	result.r = (int)(color.r + ambient->color->r * ambient->ratio);
	result.g = (int)(color.g + ambient->color->g * ambient->ratio);
	result.b = (int)(color.b + ambient->color->b * ambient->ratio);

	// Clamp values to 0-255 range
	result.r = (result.r > 255) ? 255 : result.r;
	result.g = (result.g > 255) ? 255 : result.g;
	result.b = (result.b > 255) ? 255 : result.b;

	printf("Ambient: Ratio: %.2f, Added Color: (%d, %d, %d)\n", 
           ambient->ratio, 
           (int)(ambient->color->r * ambient->ratio),
           (int)(ambient->color->g * ambient->ratio),
           (int)(ambient->color->b * ambient->ratio));

	return (result);
}

t_color calculate_ambient(t_color sphere_color, t_ambient *ambient)
{
    t_color ambient_color;
    ambient_color.r = (int)(sphere_color.r * ambient->ratio);
    ambient_color.g = (int)(sphere_color.g * ambient->ratio);
    ambient_color.b = (int)(sphere_color.b * ambient->ratio);
    return ambient_color;
}

t_color	ft_calculate_lighting(t_data *data, t_hit hit)
{
	t_color	diffuse_color;
	t_color final_color;

	printf("Sphere Color: (%d, %d, %d)\n", 
           hit.sphere->color->r, hit.sphere->color->g, hit.sphere->color->b);
	
	t_color ambient_color = calculate_ambient(*hit.sphere->color, data->ambient);
	diffuse_color = ft_calculate_diffuse(hit, data->light, *hit.sphere->color);
	final_color.r = (int)fmin(255, ambient_color.r + diffuse_color.r);
	final_color.g = (int)fmin(255, ambient_color.g + diffuse_color.g);
	final_color.b = (int)fmin(255, ambient_color.b + diffuse_color.b);
	printf("Final Color: (%d, %d, %d)\n", 
           final_color.r, final_color.g, final_color.b);
	return (final_color);
}
