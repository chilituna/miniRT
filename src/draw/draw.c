/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/11 12:08:54 by aarponen         ###   ########.fr       */
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

void	ft_init_hit(t_hit *hit)
{
	hit->distance = INFINITY;
	hit->sphere = NULL;
	hit->plane = NULL;
	hit->cylinder = NULL;
}

void	ft_draw_pixel(t_data *data, int x, int y)
{
	t_hit		hit_result;
	t_hit		tmp_hit;
	t_vector	pixel_center;
	t_ray		ray;

	ft_init_hit(&hit_result);
	ft_init_hit(&tmp_hit);
	pixel_center = ft_calculate_pixel_center(data->camera, x, y);
	ray.direction = ft_subtract(&pixel_center, &data->camera->origin);
	ray.direction = ft_normalize(&ray.direction);
	ray.origin = data->camera->origin;
	if (data->sphere)
		hit_result = ft_hit_sphere(data, ray);
	if (data->plane)
		tmp_hit = ft_hit_plane(data, ray);
	if (tmp_hit.distance < hit_result.distance)
		hit_result = tmp_hit;
	if (data->cylinder)
		tmp_hit = ft_hit_cylinder(data, ray);
	if (tmp_hit.distance < hit_result.distance)
		hit_result = tmp_hit;
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
	printf("Drawing scene...\n");
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_draw_pixel(data, x, y);
			x++;
		}
		y++;
	}
	printf("\rDrawing done.          \n");
}
