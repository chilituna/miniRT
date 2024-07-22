/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:46:59 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:32:22 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Clean the scene data
void	ft_clean_data(t_data *data)
{
	if (data->ambient)
		free(data->ambient);
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
}

// Free all the allocated memory
void	ft_free_all(t_data *data)
{
	ft_clean_data(data);
	if (data->mlx->img)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	if (data->mlx->win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx->mlx)
		mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
	free(data);
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

// Free two 2D arrays
void	ft_free_array_2(char **arr, char **arr2)
{
	ft_free_array(arr);
	ft_free_array(arr2);
}

// Free three 2D arrays
void	ft_free_array_3(char **arr, char **arr2, char **arr3)
{
	ft_free_array(arr);
	ft_free_array(arr2);
	ft_free_array(arr3);
}
