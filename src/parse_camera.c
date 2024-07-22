/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:20 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:41:15 by aarponen         ###   ########.fr       */
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
}

void	ft_check_vectors(char **arr, char **vec, t_data *data)
{
	if (ft_atof(vec[0]) < -1 || ft_atof(vec[0]) > 1 || ft_atof(vec[1]) < -1
		|| ft_atof(vec[1]) > 1 || ft_atof(vec[2]) < -1 || ft_atof(vec[2]) > 1)
		ft_error_and_free_2("Invalid camera vector value\n", arr, vec, data);
}

void	ft_check_pos(char **pos, char **arr, t_data *data)
{
	if (pos[0] == NULL || pos[1] == NULL || pos[2] == NULL || pos[3] != NULL)
		ft_error_and_free_2("Invalid camera position\n", arr, pos, data);
}

// Initialize the camera struct
void	ft_init_camera(t_data *data)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		ft_error("Failed to allocate memory for camera\n", data);
	data->camera = camera;
}

// Parse the camera line
void	ft_parse_camera(char *line, t_data *data)
{
	char	**arr;
	char	**pos;
	char	**vec;

	// TODO: Add free(line) for all error cases
	if (data->camera)
		ft_error("Duplicate camera\n", data);
	ft_init_camera(data);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	if (arr[0][1] || arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		ft_error_and_free("Invalid camera\n", arr, data);
	while (ft_isspace(*arr[1]))
		arr[1]++;
	pos = ft_split(arr[1], ',');
	ft_check_pos(pos, arr, data);
	while (ft_isspace(*arr[2]))
		arr[2]++;
	vec = ft_split(arr[2], ',');
	ft_check_vectors(arr, vec, data);
	while (ft_isspace(*arr[3]))
		arr[3]++;
	if (ft_atof(arr[3]) < 0 || ft_atof(arr[3]) > 180)
		ft_error_and_free_2("Invalid camera fov\n", arr, pos, data);
	ft_set_camera(data->camera, arr, pos, vec);
	ft_free_array_3(arr, pos, vec);
}
