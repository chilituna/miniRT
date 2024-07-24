/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:19:33 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/24 19:19:39 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Set the camera struct
void	ft_set_camera(t_camera *camera, char **arr, char **pos, char **vec)
{
	camera->origin_x = ft_atof(pos[0]);
	camera->origin_y = ft_atof(pos[1]);
	camera->origin_z = ft_atof(pos[2]);
	camera->vector_x = ft_atof(vec[0]);
	camera->vector_y = ft_atof(vec[1]);
	camera->vector_z = ft_atof(vec[2]);
	camera->fov = ft_atof(arr[3]);
	printf("Camera set:\n");
	printf("Position: %f, %f, %f\n", camera->origin_x,
		camera->origin_y, camera->origin_z);
	printf("Vector: %f, %f, %f\n", camera->vector_x,
		camera->vector_y, camera->vector_z);
	printf("FOV: %f\n", camera->fov);
	ft_free_array(arr);
	ft_free_array(pos);
	ft_free_array(vec);
}
