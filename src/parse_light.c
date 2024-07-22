/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:46:50 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:41:19 by aarponen         ###   ########.fr       */
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
	printf("Light set:\n");
	printf("Position: %f, %f, %f\n", light->origin_x,
		light->origin_y, light->origin_z);
	printf("Ratio: %f\n", light->ratio);
}

// Initialize the light struct
void	ft_init_light(t_data *data)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		ft_error("Failed to allocate memory for light\n", data);
	data->light = light;
}

// Parse the light line
void	ft_parse_light(char *line, t_data *data)
{
	char	**arr;
	char	**pos;

	// TODO: Add free(line) for all error cases
	if (data->light)
		ft_error("Duplicate light\n", data);
	ft_init_light(data);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	if (arr[0][1] || arr[1] == NULL || arr[2] == NULL)
		ft_error_and_free("Invalid light\n", arr, data);
	while (ft_isspace(*arr[1]))
		arr[1]++;
	pos = ft_split(arr[1], ',');
	if (pos[0] == NULL || pos[1] == NULL || pos[2] == NULL || pos[3] != NULL)
		ft_error_and_free_2("Invalid light position\n", arr, pos, data);
	while (ft_isspace(*arr[2]))
		arr[2]++;
	if (ft_atof(arr[2]) < 0 || ft_atof(arr[2]) > 1)
		ft_error_and_free("Invalid light ratio\n", arr, data);
	ft_set_light(data->light, arr, pos);
	ft_free_array_2(arr, pos);
}
