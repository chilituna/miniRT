/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:10:46 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/24 19:51:10 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Initialize the ambient lighting struct
void	ft_init_ambient(t_data *data, char *line)
{
	t_ambient	*ambient;

	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient)
		ft_parsing_error("Failed to malloc ambient lighting\n", data, line);
	data->ambient = ambient;
}

void	ft_set_amblight(t_ambient *ambient, char **arr, char **rgb)
{
	ambient->ratio = ft_atof(arr[1]);
	ambient->color_r = ft_atoi(rgb[0]);
	ambient->color_g = ft_atoi(rgb[1]);
	ambient->color_b = ft_atoi(rgb[2]);
	printf("Ambient light set:\n");
	printf("Ratio: %f\n", ambient->ratio);
	printf("Color: %d, %d, %d\n", ambient->color_r, ambient->color_g,
		ambient->color_b);
}

void	ft_check_ambient_rgb(char **rgb, char **arr, t_data *data, char *line)
{
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		ft_free_array(arr);
		ft_free_array(rgb);
		ft_parsing_error("Invalid ambient lighting rgb\n", data, line);
	}
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0
		|| ft_atoi(rgb[2]) > 255)
	{
		ft_free_array(arr);
		ft_free_array(rgb);
		ft_parsing_error("Invalid ambient lighting rgb value\n", data, line);
	}
}

void	ft_check_ambient_ratio(char **arr, t_data *data, char *line)
{
	if (ft_atof(arr[1]) < 0 || ft_atof(arr[1]) > 1)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid ambient lighting ratio\n", data, line);
	}
}

// Parse the ambient lighting line
void	ft_parse_ambient(char *line, t_data *data)
{
	char	**arr;
	char	**rgb;

	if (data->ambient)
		ft_parsing_error("Duplicate ambient lighting\n", data, line);
	ft_init_ambient(data, line);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	if (arr[0][1] != '\0' || arr[1] == NULL || arr[2] == NULL || arr[3] != NULL)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid ambient lighting\n", data, line);
	}
	while (ft_isspace(*arr[1]))
		arr[1]++;
	while (ft_isspace(*arr[2]))
		arr[2]++;
	rgb = ft_split(arr[2], ',');
	ft_check_ambient_rgb(rgb, arr, data, line);
	ft_check_ambient_ratio(arr, data, line);
	ft_set_amblight(data->ambient, arr, rgb);
	ft_free_array(arr);
	ft_free_array(rgb);
}
