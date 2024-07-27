/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:37:36 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/27 10:15:32 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Replace all whitespace with a single space
void	ft_normalize_whitespace(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line))
			*line = ' ';
		line++;
	}
}

// Remove white spave in the beginning of each line in arr
void	ft_remove_whitespace(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		while (ft_isspace(*arr[i]))
			arr[i]++;
		i++;
	}
}

// put a pixel to the image
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
