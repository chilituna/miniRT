/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:38:01 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 14:50:25 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_launch_mlx(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	mlx_key_hook(data->mlx->win, ft_key_handle, data);
	mlx_loop(data->mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argv;
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error("Malloc failed\n");
	ft_init_data(data);
	ft_parse_scene(argv[1], data);
	ft_launch_mlx(data);
	return (0);
}
