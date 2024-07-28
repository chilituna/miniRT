/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:50:56 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/28 15:45:09 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Inialized the plane struct and add to linked list

void	ft_init_plane_2(t_data *data, t_plane *new_plane)
{
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

void	ft_init_plane(t_data *data, char *line)
{
	t_plane		*new_plane;
	t_vector	*origin;
	t_vector	*orientation;
	t_color		*color;

	new_plane = (t_plane *)malloc(sizeof(t_plane));
	if (!new_plane)
		ft_parsing_error("Failed to allocate memory for plane\n", data, line);
	origin = (t_vector *)malloc(sizeof(t_vector));
	if (!origin)
		ft_parsing_error("Failed to malloc plane origin\n", data, line);
	orientation = (t_vector *)malloc(sizeof(t_vector));
	if (!orientation)
		ft_parsing_error("Failed to malloc plane orientation\n", data, line);
	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		ft_parsing_error("Failed to malloc plane color\n", data, line);
	new_plane->origin = origin;
	new_plane->orientation = orientation;
	new_plane->color = color;
	ft_init_plane_2(data, new_plane);
}

void	ft_set_plane(t_plane *plane, char **pos, char **vec, char **rgb)
{
	plane->origin->x = ft_atof(pos[0]);
	plane->origin->y = ft_atof(pos[1]);
	plane->origin->z = ft_atof(pos[2]);
	plane->orientation->x = ft_atof(vec[0]);
	plane->orientation->y = ft_atof(vec[1]);
	plane->orientation->z = ft_atof(vec[2]);
	plane->color->r = ft_atoi(rgb[0]);
	plane->color->g = ft_atoi(rgb[1]);
	plane->color->b = ft_atoi(rgb[2]);
	printf("PLANE\n");
	printf("- Position: %f, %f, %f\n", plane->origin->x,
		plane->origin->y, plane->origin->z);
	printf("- Vector: %f, %f, %f\n", plane->orientation->x,
		plane->orientation->y, plane->orientation->z);
	printf("- Color: %d, %d, %d\n", plane->color->r, plane->color->g,
		plane->color->b);
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
