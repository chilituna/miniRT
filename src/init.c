/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:48:38 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:42:48 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
		ft_error("malloc failed\n", data);
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->img = NULL;
	data->mlx->addr = NULL;
	data->mlx->bpp = 0;
	data->mlx->line_length = 0;
	data->mlx->endian = 0;
}
