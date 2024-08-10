/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:31:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/10 17:10:11 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"



// set up basis vectors
void	ft_set_camera_vectors(t_camera *camera)
{
	t_vector	world_up;

	world_up.x = 0.0f;
	world_up.y = 1.0f;
	world_up.z = 0.0f;
	if (fabs(camera->direction.x) < 1e-6 && fabs(camera->direction.z) < 1e-6)
		world_up = (t_vector){1.0f, 0.0f, 0.0f};
	camera->right = ft_cross(&camera->direction, &world_up);
	camera->right = ft_normalize(&camera->right);
	camera->up = ft_cross(&camera->right, &camera->direction);
	camera->up = ft_normalize(&camera->up);
}

void	ft_set_pixel00(t_camera *camera, t_vector x, t_vector y)
{
	t_vector	upper_left_corner;
	t_vector	focal_vector;

	y = ft_scale(&y, 0.5f);
	x = ft_scale(&x, 0.5f);
	focal_vector.x = camera->direction.x * camera->focal_length;
	focal_vector.y = camera->direction.y * camera->focal_length;
	focal_vector.z = camera->direction.z * camera->focal_length;
	upper_left_corner = ft_add(&camera->origin, &focal_vector);
	upper_left_corner = ft_subtract(&upper_left_corner, &x);
	upper_left_corner = ft_subtract(&upper_left_corner, &y);
	camera->pixel00_location = ft_add(&camera->pixel_delta_x,
			&camera->pixel_delta_y);
	camera->pixel00_location = ft_scale(&camera->pixel00_location, 0.5f);
	camera->pixel00_location = ft_add(&upper_left_corner,
			&camera->pixel00_location);
}

// Set up camera:
// Normalize the direction vector
// Set focal length to 1.0f
// Convert fov to radians
// Set basis vectors
// Calculate viewport size based on fov
// Calculate viewport vectors in world space
// Calculate pixel deltas = distance between pixels
// Calculate upper left corner of viewport
// Calculate pixel00 location = first pixel location
void	ft_setup_camera(t_camera *camera)
{
	float		viewport_height;
	float		viewport_width;
	t_vector	viewport_x;
	t_vector	viewport_y;

	camera->direction = ft_normalize(&camera->direction);
	camera->fov *= M_PI / 180.0f;
	camera->focal_length = 1.0f;
	ft_set_camera_vectors(camera);
	viewport_width = 2.0f * tan(camera->fov / 2.0f);
	viewport_height = viewport_width * (float)HEIGHT / (float)WIDTH;
	viewport_x = ft_scale(&camera->right, viewport_width);
	viewport_y = ft_scale(&camera->up, viewport_height);
	viewport_y.y = -viewport_y.y;
	camera->pixel_delta_x = ft_scale(&viewport_x, 1.0f / (float)WIDTH);
	camera->pixel_delta_y = ft_scale(&viewport_y, 1.0f / (float)HEIGHT);
	ft_set_pixel00(camera, viewport_x, viewport_y);
}
