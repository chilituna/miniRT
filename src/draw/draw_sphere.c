/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:05:52 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/27 17:39:39 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


//draw sphere
void	ft_draw_sphere(t_data *data)
{
	t_sphere	*sphere;
	int			x;
	int			y;
	int			r;
	int			center_x;
	int			center_y;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;

	sphere = data->sphere;
	while (sphere)
	{
		r = sphere->diameter / 2;
		x = 0;
		while (x < WIDTH)
		{
			y = 0;
			while (y < HEIGHT)
			{
				if ((x - center_x - sphere->origin_x) * (x - center_x - sphere->origin_x)
					+ (y - center_y - sphere->origin_y) * (y - center_y - sphere->origin_y) <= r * r)
					ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(0, sphere->color_r, sphere->color_g, sphere->color_b));
				y++;
			}
			x++;
		}
		sphere = sphere->next;
	}
}
