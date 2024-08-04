/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:50:56 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/04 16:48:34 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Inialized the plane struct and add to linked list
void	ft_init_plane(t_data *data, char *line)
{
	t_plane		*new_plane;

	new_plane = (t_plane *)malloc(sizeof(t_plane));
	if (!new_plane)
		ft_parsing_error("Failed to allocate memory for plane\n", data, line);
	if (data->plane)
	{
		new_plane->next = data->plane;
		data->plane = new_plane;
	}
	else
	{
		data->plane = new_plane;
		data->plane->next = NULL;
	}
}

void	ft_set_plane(t_plane *plane, char **pos, char **vec, char **rgb)
{
	plane->origin.x = ft_atof(pos[0]);
	plane->origin.y = ft_atof(pos[1]);
	plane->origin.z = ft_atof(pos[2]);
	plane->orientation.x = ft_atof(vec[0]);
	plane->orientation.y = ft_atof(vec[1]);
	plane->orientation.z = ft_atof(vec[2]);
	plane->color.r = ft_atoi(rgb[0]);
	plane->color.g = ft_atoi(rgb[1]);
	plane->color.b = ft_atoi(rgb[2]);
	ft_free_array(pos);
	ft_free_array(vec);
	ft_free_array(rgb);
}

void	ft_check_plane_input(char **arr, t_data *data, char *line)
{
	if (arr[0][2] || arr[1] == NULL || arr[2] == NULL || arr[3] == NULL
		|| arr[4] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid plane input\n", data, line);
	}
}

// Parse plane values
void	ft_parse_plane(char *line, t_data *data)
{
	char	**arr;
	char	**pos;
	char	**rgb;
	char	**vec;

	ft_init_plane(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	ft_check_plane_input(arr, data, line);
	ft_remove_whitespace(arr);
	pos = ft_split(arr[1], ',');
	if (ft_check_pos(pos, arr))
		ft_parsing_error("Invalid plane position\n", data, line);
	vec = ft_split(arr[2], ',');
	if (ft_check_vectors(arr, pos, vec))
		ft_parsing_error("Invalid plane vector\n", data, line);
	rgb = ft_split(arr[3], ',');
	if (ft_check_rgb(arr, rgb))
	{
		ft_free_array(pos);
		ft_free_array(vec);
		ft_parsing_error("Invalid plane color\n", data, line);
	}
	ft_set_plane(data->plane, pos, vec, rgb);
	ft_free_array(arr);
}
