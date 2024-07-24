/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:44:02 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/24 20:01:31 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_create_window(t_data *data)
{
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->mlx->win)
		ft_error("mlx_new_window failed\n", data);
}

// create image, get the address and set the values
void	ft_create_image(t_data *data)
{
	data->mlx->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	if (!data->mlx->img)
		ft_error("mlx_new_image failed\n", data);
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bpp,
			&data->mlx->line_length, &data->mlx->endian);
	if (!data->mlx->addr)
		ft_error("mlx_get_data_addr failed\n", data);
}

void	ft_launch_mlx(t_data *data)
{
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		ft_error("mlx_init failed\n", data);
	ft_create_window(data);
	ft_create_image(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	mlx_key_hook(data->mlx->win, ft_key_handle, data);
	mlx_hook(data->mlx->win, 17, 0, ft_mouse_quit, data);
	mlx_loop(data->mlx->mlx);
}
