/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:20 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/04 00:01:09 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Initialize the camera struct
void	ft_init_camera(t_data *data, char *line)
{
	t_camera	*camera;
	t_vector	*origin;
	t_vector	*direction;

	if (data->camera)
		ft_parsing_error("Duplicate camera\n", data, line);
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		ft_parsing_error("Failed to allocate memory for camera\n", data, line);
	origin = (t_vector *)malloc(sizeof(t_vector));
	if (!origin)
		ft_parsing_error("Failed to malloc camera origin\n", data, line);
	direction = (t_vector *)malloc(sizeof(t_vector));
	if (!direction)
		ft_parsing_error("Failed to malloc camera direction\n", data, line);
	camera->origin = origin;
	camera->direction = direction;
	data->camera = camera;
}

// Set the camera struct
// Normalize the direction vector
// Set focal length to 1.0f
// Convert fov to radians
void	ft_set_camera(t_camera *camera, char **arr, char **pos, char **vec)
{
	float		length;

	camera->origin->x = ft_atof(pos[0]);
	camera->origin->y = ft_atof(pos[1]);
	camera->origin->z = ft_atof(pos[2]);
	camera->direction->x = ft_atof(vec[0]);
	camera->direction->y = ft_atof(vec[1]);
	camera->direction->z = ft_atof(vec[2]);
	length = sqrt(camera->direction->x * camera->direction->x
			+ camera->direction->y * camera->direction->y
			+ camera->direction->z * camera->direction->z);
	camera->direction->x /= length;
	camera->direction->z /= length;
	camera->direction->y /= length;
	camera->fov = ft_atof(arr[3]);
	camera->fov *= M_PI / 180.0f;
	camera->focal_length = 1.0f;
}

int	ft_check_fov(char **arr, char **pos, char **vec)
{
	if (ft_atof(arr[3]) < 0 || ft_atof(arr[3]) > 180)
	{
		ft_free_array(pos);
		ft_free_array(vec);
		return (1);
	}
	return (0);
}

void	ft_check_camera_input(char **arr, t_data *data, char *line)
{
	if (arr[0][1] || arr[1] == NULL || arr[2] == NULL || arr[3] == NULL
		|| arr[4] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid camera input\n", data, line);
	}
}

// Parse the camera line
void	ft_parse_camera(char *line, t_data *data)
{
	char	**arr;
	char	**pos;
	char	**vec;

	ft_init_camera(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	ft_check_camera_input(arr, data, line);
	ft_remove_whitespace(arr);
	pos = ft_split(arr[1], ',');
	if (ft_check_pos(pos, arr))
		ft_parsing_error("Invalid camera position\n", data, line);
	vec = ft_split(arr[2], ',');
	if (ft_check_vectors(arr, pos, vec))
		ft_parsing_error("Invalid camera vector\n", data, line);
	if (ft_check_fov(arr, pos, vec))
		ft_parsing_error("Invalid camera fov\n", data, line);
	ft_set_camera(data->camera, arr, pos, vec);
	ft_free_array(arr);
	ft_free_array(pos);
	ft_free_array(vec);
}
