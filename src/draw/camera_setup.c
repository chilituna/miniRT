/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:31:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/07 19:27:28 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// cross priduct of two vectors
// needed to calculate the right and up vectors
t_vector	ft_cross(t_vector *a, t_vector *b)
{
	t_vector	cross;

	cross.x = a->y * b->z - a->z * b->y;
	cross.y = a->z * b->x - a->x * b->z;
	cross.z = a->x * b->y - a->y * b->x;
	return (cross);
}

// set up basis vectors
void	ft_set_camera_vectors(t_camera *camera)
{
	camera->right = ft_cross(&camera->direction, &(t_vector){0.0f, 1.0f, 0.0f});
	camera->right = ft_normalize(&camera->right);
	camera->up = ft_cross(&camera->right, &camera->direction);
	camera->up = ft_normalize(&camera->up);
	printf("right: %f %f %f\n", camera->right.x, camera->right.y, camera->right.z);
	printf("up: %f %f %f\n", camera->up.x, camera->up.y, camera->up.z);
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
	t_vector	upper_left_corner;
	float		viewport_height;
	float		viewport_width;
	t_vector	viewport_x;
	t_vector	viewport_y;
	t_vector	focal_vector;

	camera->direction = ft_normalize(&camera->direction);
	camera->fov *= M_PI / 180.0f;
	camera->focal_length = 1.0f;
	ft_set_camera_vectors(camera);
	viewport_width = 2.0f * tan(camera->fov / 2.0f);
	viewport_height = viewport_width * (float)HEIGHT / (float)WIDTH;
	printf("viewport_width: %f\n", viewport_width);
	printf("viewport_height: %f\n", viewport_height);
	viewport_x = ft_scale(&camera->right, viewport_width);
	viewport_y = ft_scale(&camera->up, viewport_height);
	viewport_y.y = -viewport_y.y;
	printf("viewport_x: %f %f %f\n", viewport_x.x, viewport_x.y, viewport_x.z);
	printf("viewport_y: %f %f %f\n", viewport_y.x, viewport_y.y, viewport_y.z);
	camera->pixel_delta_x = ft_scale(&viewport_x, 1.0f / (float)WIDTH);
	camera->pixel_delta_y = ft_scale(&viewport_y, 1.0f / (float)HEIGHT);
	printf("pixel_delta_x: %f %f %f\n", camera->pixel_delta_x.x,
		camera->pixel_delta_x.y, camera->pixel_delta_x.z);
	printf("pixel_delta_y: %f %f %f\n", camera->pixel_delta_y.x,
		camera->pixel_delta_y.y, camera->pixel_delta_y.z);
	viewport_y = ft_scale(&viewport_y, 0.5f);
	viewport_x = ft_scale(&viewport_x, 0.5f);
	focal_vector.x = camera->direction.x * camera->focal_length;
	focal_vector.y = camera->direction.y * camera->focal_length;
	focal_vector.z = camera->direction.z * camera->focal_length;
	upper_left_corner = ft_subtract(&camera->origin, &focal_vector);
	upper_left_corner = ft_subtract(&upper_left_corner, &viewport_x);
	upper_left_corner = ft_subtract(&upper_left_corner, &viewport_y);
	printf("upper_left_corner: %f %f %f\n", upper_left_corner.x,
		upper_left_corner.y, upper_left_corner.z);
	camera->pixel00_location = ft_add(&camera->pixel_delta_x, &camera->pixel_delta_y);
	camera->pixel00_location = ft_scale(&camera->pixel00_location, 0.5f);
	camera->pixel00_location = ft_add(&upper_left_corner, &camera->pixel00_location);
	printf("pixel00_location: %f %f %f\n", camera->pixel00_location.x,
		camera->pixel00_location.y, camera->pixel00_location.z);
}
