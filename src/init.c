/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:48:38 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 16:04:00 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_create_window(t_data *data)
{
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->mlx->win)
	{
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx);
		ft_error("mlx_new_window failed\n");
	}
}

// create image, get the address and set the values
void	ft_create_image(t_data *data)
{
	data->mlx->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	if (!data->mlx->img)
	{
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx);
		ft_error("mlx_new_image failed\n");
	}
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bpp,
			&data->mlx->line_length, &data->mlx->endian);
	if (!data->mlx->addr)
	{
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx);
		ft_error("mlx_get_data_addr failed\n");
	}
}

void	ft_init_data(t_data *data)
{
	data->mlx = NULL;
	data->ambient = NULL;
	data->camera = NULL;
	data->light = NULL;
	data->sphere = NULL;
	data->plane = NULL;
	data->cylinder = NULL;
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		ft_error("malloc failed\n");
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->img = NULL;
	data->mlx->addr = NULL;
	data->mlx->bpp = 0;
	data->mlx->line_length = 0;
	data->mlx->endian = 0;
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		ft_error("mlx_init failed\n");
	ft_create_window(data);
	ft_create_image(data);
}
