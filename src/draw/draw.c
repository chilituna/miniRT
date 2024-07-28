/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:43 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/28 12:08:00 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


// Draw the scene
// Using doubles for color calculations and then converting them to integers
// ensures that the gradient is calculated with higher precision and smoothness.
void	ft_draw_scene(t_data *data)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		printf("\rDraw lines remaining: %d  ", HEIGHT - y);
		while (x < WIDTH)
		{
			color = ft_calculate_color(x, y);
			ft_my_mlx_pixel_put(data->mlx, x, y, color);
			x++;
		}
		y++;
		if (data->sphere)
			ft_draw_sphere(data);
	}
	printf("\rDrawing done.          \n");
}
