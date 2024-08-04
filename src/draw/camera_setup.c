/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sveselov <sveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:31:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/04 18:04:25 by sveselov         ###   ########.fr       */
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
void	ft_set_camera_vectors(t_camera *camera, t_vector *forward)
{
	camera->right = ft_cross(forward, &(t_vector){0.0f, 1.0f, 0.0f});
	camera->right = ft_normalize(&camera->right);
	camera->up = ft_cross(&camera->right, forward);
	camera->up = ft_normalize(&camera->up);
}

// Set up camera:
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
	t_vector	forward;

	forward = ft_scale(&camera->direction, -1.0f);
	ft_set_camera_vectors(camera, &forward);
	viewport_width = 2.0f * tan(camera->fov / 2.0f);
	viewport_height = viewport_width * (float)HEIGHT / (float)WIDTH;
	viewport_x = ft_scale(&camera->right, viewport_width);
	viewport_y = ft_scale(&camera->up, viewport_height);
	camera->pixel_delta_x = ft_scale(&viewport_x, 1.0f / (float)WIDTH);
	camera->pixel_delta_y = ft_scale(&viewport_y, 1.0f / (float)HEIGHT);
	upper_left_corner = ft_subtract(&camera->origin, &camera->direction);
	viewport_x = ft_scale(&viewport_x, 0.5f);
	viewport_y = ft_scale(&viewport_y, 0.5f);
	upper_left_corner = ft_subtract(&upper_left_corner, &viewport_x);
	upper_left_corner = ft_subtract(&upper_left_corner, &viewport_y);
	camera->pixel00_location = ft_add(&camera->pixel_delta_x,
			&camera->pixel_delta_y);
	camera->pixel00_location = ft_scale(&camera->pixel00_location, 0.5f);
	camera->pixel00_location = ft_add(&upper_left_corner,
			&camera->pixel00_location);
}
