/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/07 23:53:49 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	ft_calculate_pixel_center(t_camera *camera, int x, int y)
{
	t_vector	pixel_center;
	t_vector	scaled_x;
	t_vector	scaled_y;

	scaled_x = ft_scale(&camera->pixel_delta_x, (float)x);
	scaled_y = ft_scale(&camera->pixel_delta_y, (float)y);
	pixel_center = ft_add(&scaled_x, &scaled_y);
	pixel_center = ft_add(&pixel_center, &camera->pixel00_location);
	return (pixel_center);
}

// Calculate the color and put it to image:
// just to test out, calculate color based on the xyz hitpoint
void	ft_put_color(t_data *data, int x, int y, t_hit hit)
{
	t_vector	diff = ft_subtract(&data->light->origin, &hit.hitpoint);
	t_vector	light_dir = ft_normalize(&diff);
	float		diffuse = ft_calculate_diffuse_lighting(&hit.normal, &light_dir);

	t_color final_color;
	final_color.r = (int)(hit.sphere->color.r * diffuse);
	final_color.g = (int)(hit.sphere->color.g * diffuse);
	final_color.b = (int)(hit.sphere->color.b * diffuse);

	ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(1, &final_color));
}

void	ft_draw_pixel(t_data *data, int x, int y)
{
	t_hit		hit_result;
	t_vector	pixel_center;
	t_ray		ray;

	pixel_center = ft_calculate_pixel_center(data->camera, x, y);
	ray.direction = ft_subtract(&pixel_center, &data->camera->origin);
	ray.origin = data->camera->origin;
	hit_result.distance = INFINITY;
	if (data->sphere)
		hit_result = ft_hit_sphere(data, ray);
	if (hit_result.distance < INFINITY)
		ft_put_color(data, x, y, hit_result);
}

// Draw the scene:
// Iterate through the screen pixels and calculate the color for each pixel.
// Check for all objects in the scene and calculate the closest object hit.
// Color the pixel with the color of the closest object.
void	ft_draw_scene(t_data *data)
{
	int			x;
	int			y;

	y = 0;
	x = 0;
	ft_setup_camera(data->camera);
	while (y < HEIGHT)
	{
		x = 0;
		printf("\rDraw lines remaining: %d  ", HEIGHT - y);
		while (x < WIDTH)
		{
			ft_draw_pixel(data, x, y);
			x++;
		}
		y++;
	}
	printf("\rDrawing done.          \n");
}
