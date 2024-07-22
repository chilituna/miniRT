/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:46:59 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 15:22:02 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Clean the data struct and exit
void	ft_clean_data(t_data *data)
{
	if (data->ambient)
		free(data->ambient);
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
}

// Free the array
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

void	ft_free_array_2(char **arr, char **arr2)
{
	ft_free_array(arr);
	ft_free_array(arr2);
}

void	ft_free_array_3(char **arr, char **arr2, char **arr3)
{
	ft_free_array(arr);
	ft_free_array(arr2);
	ft_free_array(arr3);
}
