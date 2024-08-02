/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/02 14:54:28 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Set up camera
void	ft_setup_camera(t_camera *camera)
{
	t_vector	upper_left_corner;
	float		focal_length;
	float		viewport_height;
	float		viewport_width;
	t_vector	viewport_x;
	t_vector	viewport_y;

	focal_length = 1.0f;
	viewport_height = 2.0f;
	viewport_width = viewport_height * (float)WIDTH / (float)HEIGHT;
	viewport_x = (t_vector){viewport_width, 0.0f, 0.0f};
	viewport_y = (t_vector){0.0f, -viewport_height, 0.0f};
	camera->pixel_delta_x = ft_scale(&viewport_x, 1.0f / (float)WIDTH);
	camera->pixel_delta_y = ft_scale(&viewport_y, 1.0f / (float)HEIGHT);
	upper_left_corner = ft_subtract(camera->origin, &(t_vector){0.0f, 0.0f, focal_length});
	viewport_x = ft_scale(&viewport_x, 0.5f);
	viewport_y = ft_scale(&viewport_y, 0.5f);
	upper_left_corner = ft_subtract(&upper_left_corner, &viewport_x);
	upper_left_corner = ft_subtract(&upper_left_corner, &viewport_y);
	camera->pixel00_location = ft_add(&camera->pixel_delta_x, &camera->pixel_delta_y);
	camera->pixel00_location = ft_scale(&camera->pixel00_location, 0.5f);
	camera->pixel00_location = ft_add(&upper_left_corner, &camera->pixel00_location);
}

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

// Draw the scene:
// Iterate through the screen pixels and calculate the color for each pixel.
// Check for all objects in the scene and calculate the closest object hit.
// Color the pixel with the color of the closest object.
void	ft_draw_scene(t_data *data)
{
	int			x;
	int			y;
	t_hit		hit_result;
	t_vector	pixel_center;
	t_ray		ray;

	y = 0;
	x = 0;
	ft_setup_camera(data->camera);
	while (y < HEIGHT)
	{
		x = 0;
		printf("\rDraw lines remaining: %d  ", HEIGHT - y);
		while (x < WIDTH)
		{
			pixel_center = ft_calculate_pixel_center(data->camera, x, y);
			ray.direction = ft_subtract(&pixel_center, data->camera->origin);
			ray.origin = *data->camera->origin;
			hit_result.distance = INFINITY;
			if (data->sphere)
				hit_result = ft_hit_sphere(data, ray);
			if (hit_result.distance < INFINITY)
				ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(1, hit_result.sphere->color));
			x++;
		}
		y++;
	}
	printf("\rDrawing done.          \n");
}
