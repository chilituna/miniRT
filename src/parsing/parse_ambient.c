/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:10:46 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/02 14:50:52 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Initialize the ambient lighting struct
void	ft_init_ambient(t_data *data, char *line)
{
	t_ambient	*ambient;
	t_color		*color;

	if (data->ambient)
		ft_parsing_error("Duplicate ambient lighting\n", data, line);
	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient)
		ft_parsing_error("Failed to malloc ambient lighting\n", data, line);
	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		ft_parsing_error("Failed to malloc ambient color\n", data, line);
	ambient->color = color;
	data->ambient = ambient;
}

void	ft_set_amblight(t_ambient *ambient, char **arr, char **rgb)
{
	ambient->ratio = ft_atof(arr[1]);
	ambient->color->r = ft_atoi(rgb[0]);
	ambient->color->g = ft_atoi(rgb[1]);
	ambient->color->b = ft_atoi(rgb[2]);
}

void	ft_check_ambient_ratio(char **arr, t_data *data, char *line)
{
	if (ft_atof(arr[1]) < 0 || ft_atof(arr[1]) > 1)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid ambient lighting ratio\n", data, line);
	}
}

void	ft_check_amblight_input(char **arr, t_data *data, char *line)
{
	if (arr[0][1] || arr[1] == NULL || arr[2] == NULL || arr[3] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid ambient lighting\n", data, line);
	}
}

// Parse the ambient lighting line
void	ft_parse_ambient(char *line, t_data *data)
{
	char	**arr;
	char	**rgb;

	ft_init_ambient(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	ft_check_amblight_input(arr, data, line);
	ft_remove_whitespace(arr);
	ft_check_ambient_ratio(arr, data, line);
	rgb = ft_split(arr[2], ',');
	if (ft_check_rgb(rgb, arr))
		ft_parsing_error("Invalid ambient lighting rgb\n", data, line);
	ft_set_amblight(data->ambient, arr, rgb);
	ft_free_array(arr);
	ft_free_array(rgb);
}
