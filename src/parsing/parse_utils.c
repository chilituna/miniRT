/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:16:54 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/20 18:24:26 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Position needs to have 3 values
int	ft_check_pos(char **pos, char **arr)
{
	if (pos[0] == NULL || pos[1] == NULL || pos[2] == NULL || pos[3] != NULL)
	{
		ft_free_array(arr);
		ft_free_array(pos);
		return (1);
	}
	return (0);
}

// Vector needs to have 3 values
// and the values need to be between -1 and 1
int	ft_check_vectors(char **arr, char **pos, char **vec)
{
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL || vec[3] != NULL)
	{
		ft_free_array(arr);
		ft_free_array(pos);
		ft_free_array(vec);
		return (1);
	}
	if (ft_atof(vec[0]) < -1 || ft_atof(vec[0]) > 1 || ft_atof(vec[1]) < -1
		|| ft_atof(vec[1]) > 1 || ft_atof(vec[2]) < -1 || ft_atof(vec[2]) > 1)
	{
		ft_free_array(arr);
		ft_free_array(pos);
		ft_free_array(vec);
		return (1);
	}
	return (0);
}

// RGB needs to have 3 values
// and the values need to be between 0 and 255
int	ft_check_rgb(char **arr, char **rgb)
{
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		ft_free_array(arr);
		ft_free_array(rgb);
		return (1);
	}
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0
		|| ft_atoi(rgb[2]) > 255)
	{
		ft_free_array(arr);
		ft_free_array(rgb);
		return (1);
	}
	return (0);
}

int	ft_check_rgb_2(char **arr, char **pos, char **vec, char **rgb)
{
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		ft_free_array(arr);
		ft_free_array(rgb);
		ft_free_array(pos);
		ft_free_array(vec);
		return (1);
	}
	if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
		|| ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0
		|| ft_atoi(rgb[2]) > 255)
	{
		ft_free_array(arr);
		ft_free_array(rgb);
		ft_free_array(pos);
		ft_free_array(vec);
		return (1);
	}
	return (0);
}

void	ft_check_size(char **arr, int i, t_data *data, char *l)
{
	if (ft_atof(arr[i]) < 0)
	{
		ft_free_array(arr);
		ft_parsing_error("Invalid height or diameter", data, l);
	}
}
