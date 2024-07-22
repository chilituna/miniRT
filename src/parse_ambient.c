/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:10:46 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:40:55 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Initialize the ambient lighting struct
void	ft_init_ambient(t_data *data)
{
	t_ambient	*ambient;

	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient)
		ft_error("Failed to allocate memory for ambient lighting\n", data);
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

// Parse the ambient lighting line
void	ft_parse_ambient(char *line, t_data *data)
{
	char	**arr;
	char	**rgb;

	// TODO: Add free(line) for all error cases
	if (data->ambient)
		ft_error("Duplicate ambient lighting\n", data);
	ft_init_ambient(data);
	ft_normalize_whitespace(line);
	arr = ft_split(line, ' ');
	if (arr[0][1] != '\0' || arr[1] == NULL || arr[2] == NULL)
		ft_error_and_free("Invalid ambient lighting\n", arr, data);
	while (ft_isspace(*arr[1]))
		arr[1]++;
	if (ft_atof(arr[1]) < 0 || ft_atof(arr[1]) > 1)
		ft_error_and_free("Invalid ambient lighting ratio\n", arr, data);
	while (ft_isspace(*arr[2]))
		arr[2]++;
	rgb = ft_split(arr[2], ',');
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
		ft_error_and_free_2("Invalid ambient lighting rgb\n", arr, rgb, data);
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0
		|| ft_atoi(rgb[2]) > 255)
		ft_error_and_free_2("Invalid ambient rgb value\n", arr, rgb, data);
	ft_set_amblight(data->ambient, arr, rgb);
	ft_free_array_2(arr, rgb);
}
