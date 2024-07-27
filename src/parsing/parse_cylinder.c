/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:40:44 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/27 12:30:09 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Init the cylinder struct
// and add it to the list
void	ft_init_cylinder(t_data *data, char *l)
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!new_cylinder)
		ft_parsing_error("Failed to allocate memory for cylinder\n", data, l);
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

// Set the cylinder values
void	ft_set_cylinder(t_cylinder *cyl, char **pos, char **vec, char **rgb)
{
	cyl->origin_x = ft_atof(pos[0]);
	cyl->origin_y = ft_atof(pos[1]);
	cyl->origin_z = ft_atof(pos[2]);
	cyl->vector_x = ft_atof(vec[0]);
	cyl->vector_y = ft_atof(vec[1]);
	cyl->vector_z = ft_atof(vec[2]);
	cyl->color_r = ft_atoi(rgb[0]);
	cyl->color_g = ft_atoi(rgb[1]);
	cyl->color_b = ft_atoi(rgb[2]);
	ft_free_array(pos);
	ft_free_array(vec);
	ft_free_array(rgb);
}

void	ft_set_cylinder_2(t_cylinder *cylinder, char **arr)
{
	cylinder->diameter = ft_atof(arr[3]);
	cylinder->height = ft_atof(arr[4]);
	ft_free_array(arr);
	printf("--CYLINDER--\n");
	printf("Position: %f, %f, %f\n", cylinder->origin_x,
		cylinder->origin_y, cylinder->origin_z);
	printf("Vector: %f, %f, %f\n", cylinder->vector_x,
		cylinder->vector_y, cylinder->vector_z);
	printf("Diameter: %f\n", cylinder->diameter);
	printf("Height: %f\n", cylinder->height);
	printf("Color: %d, %d, %d\n", cylinder->color_r, cylinder->color_g,
		cylinder->color_b);
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
