/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:20 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/24 19:50:55 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Initialize the camera struct
void	ft_init_camera(t_data *data, char *line)
{
	t_camera	*camera;

	if (data->camera)
		ft_parsing_error("Duplicate camera\n", data, line);
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		ft_parsing_error("Failed to allocate memory for camera\n", data, line);
	data->camera = camera;
}

void	ft_check_vectors(char **arr, char **vec, t_data *data)
{
	if (ft_atof(vec[0]) < -1 || ft_atof(vec[0]) > 1 || ft_atof(vec[1]) < -1
		|| ft_atof(vec[1]) > 1 || ft_atof(vec[2]) < -1 || ft_atof(vec[2]) > 1)
	{
		ft_free_array(arr);
		ft_free_array(vec);
		ft_parsing_error("Invalid camera vector\n", data, arr[0]);
	}
}

void	ft_check_pos(char **pos, char **arr, t_data *data)
{
	if (pos[0] == NULL || pos[1] == NULL || pos[2] == NULL || pos[3] != NULL)
	{
		ft_free_array(arr);
		ft_free_array(pos);
		ft_parsing_error("Invalid camera position\n", data, arr[0]);
	}
}


void	ft_check_fov(char **arr, char **pos, char **vec, t_data *data, char *l)
{
	if (ft_atof(arr[3]) < 0 || ft_atof(arr[3]) > 180)
	{
		ft_free_array(arr);
		ft_free_array(pos);
		ft_free_array(vec);
		ft_parsing_error("Invalid camera fov\n", data, l);
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
	if (arr[0][1] || arr[1] == NULL || arr[2] == NULL || arr[3] == NULL
		|| arr[4] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid camera\n", data, line);
	}
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
	ft_check_fov(arr, pos, vec, data, line);
	ft_set_camera(data->camera, arr, pos, vec);
}
