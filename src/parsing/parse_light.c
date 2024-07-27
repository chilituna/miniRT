/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:46:50 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/27 10:30:15 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Set the light struct
void	ft_set_light(t_light *light, char **arr, char **pos)
{
	light->origin_x = ft_atof(pos[0]);
	light->origin_y = ft_atof(pos[1]);
	light->origin_z = ft_atof(pos[2]);
	light->ratio = ft_atof(arr[2]);
	printf("--LIGHT--\n");
	printf("Position: %f, %f, %f\n", light->origin_x,
		light->origin_y, light->origin_z);
	printf("Ratio: %f\n", light->ratio);
}

// Initialize the light struct
void	ft_init_light(t_data *data, char *line)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		ft_parsing_error("Failed to allocate memory for light\n", data, line);
	data->light = light;
}

void	ft_check_light_ratio(char **arr, char **pos, t_data *data, char *line)
{
	if (ft_atof(arr[2]) < 0 || ft_atof(arr[2]) > 1)
	{
		ft_free_array(arr);
		ft_free_array(pos);
		ft_parsing_error("Invalid light ratio\n", data, line);
	}
}

void	ft_check_light_input(char **arr, t_data *data, char *line)
{
	if (arr[0][1] || arr[1] == NULL || arr[2] == NULL || arr[3] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid light input\n", data, line);
	}
}

// Parse the light line
void	ft_parse_light(char *line, t_data *data)
{
	char	**arr;
	char	**pos;

	if (data->light)
		ft_parsing_error("Duplicate light\n", data, line);
	ft_init_light(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	ft_check_light_input(arr, data, line);
	ft_remove_whitespace(arr);
	pos = ft_split(arr[1], ',');
	if (ft_check_pos(pos, arr))
		ft_parsing_error("Invalid light position\n", data, line);
	ft_check_light_ratio(arr, pos, data, line);
	ft_set_light(data->light, arr, pos);
	ft_free_array(arr);
	ft_free_array(pos);
}
