/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:34:50 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 15:49:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Close the window with ESC
int	ft_key_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_clean_data(data);
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
		free(data->mlx);
		free(data);
		exit(0);
	}
	return (0);
}
