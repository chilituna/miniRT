/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:40:44 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/28 18:22:06 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_init_cylinder_2(t_data *data, t_cylinder *new_cylinder)
{
	if (data->cylinder)
	{
		new_cylinder->next = data->cylinder;
		data->cylinder = new_cylinder;
	}
	else
	{
		data->cylinder = new_cylinder;
		data->cylinder->next = NULL;
	}
}

// Init the cylinder struct
// and add it to the list
void	ft_init_cylinder(t_data *data, char *l)
{
	t_cylinder	*new_cylinder;
	t_vector	*origin;
	t_vector	*orientation;
	t_color		*color;

	new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!new_cylinder)
		ft_parsing_error("Failed to allocate memory for cylinder\n", data, l);
	origin = (t_vector *)malloc(sizeof(t_vector));
	if (!origin)
		ft_parsing_error("Failed to malloc cylinder origin\n", data, l);
	orientation = (t_vector *)malloc(sizeof(t_vector));
	if (!orientation)
		ft_parsing_error("Failed to malloc cylinder orientation\n", data, l);
	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		ft_parsing_error("Failed to malloc cylinder color\n", data, l);
	new_cylinder->origin = origin;
	new_cylinder->orientation = orientation;
	new_cylinder->color = color;
	ft_init_cylinder_2(data, new_cylinder);
}

void	ft_check_cylinder_input(char **arr, t_data *data, char *line)
{
	if (arr[0][2] || arr[1] == NULL || arr[2] == NULL || arr[3] == NULL
		|| arr[4] == NULL || arr[5] == NULL || arr[6] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid cylinder input\n", data, line);
	}
}

//Parse the cylinder line
void	ft_parse_cylinder(char *line, t_data *data)
{
	char	**arr;
	char	**pos;
	char	**vec;
	char	**rgb;

	ft_init_cylinder(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	ft_check_cylinder_input(arr, data, line);
	ft_remove_whitespace(arr);
	ft_check_size(arr, 3, data, line);
	ft_check_size(arr, 4, data, line);
	pos = ft_split(arr[1], ',');
	if (ft_check_pos(pos, arr))
		ft_parsing_error("Invalid cylinder position\n", data, line);
	vec = ft_split(arr[2], ',');
	if (ft_check_vectors(arr, pos, vec))
		ft_parsing_error("Invalid cylinder vector\n", data, line);
	rgb = ft_split(arr[5], ',');
	if (ft_check_rgb_2(arr, pos, vec, rgb))
		ft_parsing_error("Invalid cylinder color\n", data, line);
	ft_set_cylinder(data->cylinder, pos, vec, rgb);
	ft_set_cylinder_2(data->cylinder, arr);
}
