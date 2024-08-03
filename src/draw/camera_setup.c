/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:31:58 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/03 10:32:19 by aarponen         ###   ########.fr       */
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
