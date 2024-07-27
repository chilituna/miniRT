/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 08:52:00 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/27 18:17:50 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Initialize the sphere struct
// and add it to linked list
void	ft_init_sphere(t_data *data, char *line)
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!new_sphere)
		ft_parsing_error("Failed to allocate memory for sphere\n", data, line);
	if (data->sphere)
	{
		new_sphere->next = data->sphere;
		data->sphere = new_sphere;
	}
	else
	{
		data->sphere = new_sphere;
		data->sphere->next = NULL;
	}
}

// Set sphere values
void	ft_set_sphere(t_sphere *sphere, char **arr, char **pos, char **rgb)
{
	sphere->origin_x = ft_atof(pos[0]);
	sphere->origin_y = ft_atof(pos[1]);
	sphere->origin_z = ft_atof(pos[2]);
	sphere->diameter = ft_atof(arr[2]);
	sphere->color_r = ft_atoi(rgb[0]);
	sphere->color_g = ft_atoi(rgb[1]);
	sphere->color_b = ft_atoi(rgb[2]);
	printf("SPHERE\n");
	printf("- Position: %f, %f, %f\n", sphere->origin_x,
		sphere->origin_y, sphere->origin_z);
	printf("- Diameter: %f\n", sphere->diameter);
	printf("- Color: %d, %d, %d\n", sphere->color_r, sphere->color_g,
		sphere->color_b);
}

void	ft_check_sphere_input(char **arr, t_data *data, char *line)
{
	if (arr[0][2] || arr[1] == NULL || arr[2] == NULL || arr[3] == NULL
		|| arr[4] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid sphere input\n", data, line);
	}
}

// Parse sphere information
void	ft_parse_sphere(char *line, t_data *data)
{
	char	**arr;
	char	**pos;
	char	**rgb;

	ft_init_sphere(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	ft_check_sphere_input(arr, data, line);
	ft_remove_whitespace(arr);
	ft_check_size(arr, 2, data, line);
	pos = ft_split(arr[1], ',');
	if (ft_check_pos(pos, arr))
		ft_parsing_error("Invalid sphere position\n", data, line);
	rgb = ft_split(arr[3], ',');
	if (ft_check_rgb(arr, rgb))
	{
		ft_free_array(pos);
		ft_parsing_error("Invalid sphere color\n", data, line);
	}
	ft_set_sphere(data->sphere, arr, pos, rgb);
	ft_free_array(arr);
	ft_free_array(pos);
	ft_free_array(rgb);
}
