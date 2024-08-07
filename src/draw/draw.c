/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/07 19:18:30 by aarponen         ###   ########.fr       */
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
	if (x == 0 && y == 0)
		printf("x = 0, y = 0 -- pixel center: %f %f %f\n", pixel_center.x, pixel_center.y, pixel_center.z);
	if (x == 400 && y == 300)
		printf("x = 399, y = 299 -- pixel center: %f %f %f\n", pixel_center.x, pixel_center.y, pixel_center.z);
	if (x == 799 && y == 599)
		printf("x = 799, y = 599 -- pixel center: %f %f %f\n", pixel_center.x, pixel_center.y, pixel_center.z);

	return (pixel_center);
}

// Calculate the color and put it to image:
// just to test out, calculate color based on the xyz hitpoint
void	ft_put_color(t_data *data, int x, int y, t_hit hit)
{
	ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(1, &hit.sphere->color));
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
	if (x == 0 && y == 0)
		printf("x = 0, y = 0 -- ray direction: %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	if (x == 400 && y == 300)
		printf("x = 399, y = 299 -- ray direction: %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	if (x == 799 && y == 599)
		printf("x = 799, y = 599 -- ray direction: %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
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
		// printf("\rDraw lines remaining: %d  ", HEIGHT - y);
		while (x < WIDTH)
		{
			ft_draw_pixel(data, x, y);
			x++;
		}
		y++;
	}
	printf("\rDrawing done.          \n");
}
