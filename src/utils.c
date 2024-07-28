/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:37:36 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/28 15:29:33 by aarponen         ###   ########.fr       */
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

// Free a 2D array
void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
