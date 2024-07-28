/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:05:52 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/28 15:46:07 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


// draw sphere
// (bx^2 + by^2)t^2 + 2(axbx + ayby)t + (ax^2 + ay^2 - r^2) = 0
// where
// a = ray origin = camera position
// b = ray direction = camera direction
// r = radius = sphere radius
// t = hit distance
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
				if ((x - center_x - sphere->origin->x) * (x - center_x - sphere->origin->x)
					+ (y - center_y - sphere->origin->y) * (y - center_y - sphere->origin->y) <= r * r)
					ft_my_mlx_pixel_put(data->mlx, x, y, ft_trgb(0, sphere->color->r, sphere->color->g, sphere->color->b));
				else
					ft_my_mlx_pixel_put(data->mlx, x, y, ft_calculate_color(x, y));
				y++;
			}
			x++;
		}
		sphere = sphere->next;
	}
}
