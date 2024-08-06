/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/07 23:54:37 by s0nia            ###   ########.fr       */
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
// void	ft_put_color(t_data *data, int x, int y, t_hit hit)
// {
// 	t_vector	diff = ft_subtract(&data->light->origin, &hit.hitpoint);
// 	t_vector	light_dir = ft_normalize(&diff);
// 	float		diffuse = ft_calculate_diffuse_lighting(&hit.normal, &light_dir);
// 	t_color final_color;

// 	printf("diffuse: %f\n", diffuse);
// 	final_color.r = (int)(hit.sphere->color.r * diffuse);
// 	final_color.g = (int)(hit.sphere->color.g * diffuse);
// 	final_color.b = (int)(hit.sphere->color.b * diffuse);

// 	ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(1, &final_color));
// }

void lighting_diagnostic(t_data *data, t_hit hit)
{
    t_vector light_dir = ft_subtract(&data->light->origin, &hit.hitpoint);
    light_dir = ft_normalize(&light_dir);
    
    float dot_product = ft_dot(&hit.normal, &light_dir);
    
    printf("Camera position: x=%.2f, y=%.2f, z=%.2f\n", data->camera->origin.x, data->camera->origin.y, data->camera->origin.z);
    printf("Camera direction: x=%.2f, y=%.2f, z=%.2f\n", data->camera->direction.x, data->camera->direction.y, data->camera->direction.z);
    printf("Hit point: x=%.2f, y=%.2f, z=%.2f\n", hit.hitpoint.x, hit.hitpoint.y, hit.hitpoint.z);
    printf("Sphere center: x=%.2f, y=%.2f, z=%.2f\n", hit.sphere->origin.x, hit.sphere->origin.y, hit.sphere->origin.z);
    printf("Light position: x=%.2f, y=%.2f, z=%.2f\n", data->light->origin.x, data->light->origin.y, data->light->origin.z);
    printf("Normal: x=%.2f, y=%.2f, z=%.2f\n", hit.normal.x, hit.normal.y, hit.normal.z);
    printf("Light direction: x=%.2f, y=%.2f, z=%.2f\n", light_dir.x, light_dir.y, light_dir.z);
    printf("Dot product: %.2f\n\n", dot_product);
}

void ft_put_color(t_data *data, int x, int y, t_hit hit)
{
	t_vector	diff = ft_subtract(&data->light->origin, &hit.hitpoint);
	t_vector	light_dir = ft_normalize(&diff);
	float		diffuse = 0.0f;
	t_color		ambient_color = {0, 0, 0};
	t_color		final_color;

	lighting_diagnostic(data, hit);
	ft_calculate_ambient_lighting(data, &ambient_color);
	printf("Ambient Color: R=%d, G=%d, B=%d\n", ambient_color.r, ambient_color.g, ambient_color.b);

	if (!ft_is_in_shadow(data, &hit.hitpoint, &light_dir))
	{
		diffuse = ft_calculate_diffuse_lighting(&hit.normal, &light_dir);
		printf("Diffuse: %.2f\n", diffuse);
	}
	final_color.r = (int)(hit.sphere->color.r * (diffuse + ambient_color.r / 255.0f));
	final_color.g = (int)(hit.sphere->color.g * (diffuse + ambient_color.g / 255.0f));
	final_color.b = (int)(hit.sphere->color.b * (diffuse + ambient_color.b / 255.0f));
	printf("Final Color before clamping: R=%d, G=%d, B=%d\n", final_color.r, final_color.g, final_color.b);
	final_color.r = fminf(final_color.r, 255);
	final_color.g = fminf(final_color.g, 255);
	final_color.b = fminf(final_color.b, 255);
	printf("Final Color after clamping: R=%d, G=%d, B=%d\n", final_color.r, final_color.g, final_color.b);

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
	printf("y = %d\n", y);
	printf("HEIGHT = %d\n", HEIGHT);
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
