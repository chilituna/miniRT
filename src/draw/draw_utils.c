/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:28:31 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/29 10:44:07 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// put a pixel to the image
void	ft_my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

//bitshifts to create a trgb color
int	ft_trgb(int t, t_color *color)
{
	return (t << 24 | color->r << 16 | color->g << 8 | color->b);
}

// Create a trgb color for gradient
int	ft_create_trgb(int t, double r, double g, double b)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(255.999 * r);
	green = (int)(255.999 * g);
	blue = (int)(255.999 * b);
	return (t << 24 | red << 16 | green << 8 | blue);
}

// Creating a color gradient
// Using doubles for color calculations and then converting them to integers
// ensures that the gradient is calculated with higher precision and smoothness.
// 
int	ft_calculate_gradient(int x, int y)
{
	double	r;
	double	g;
	double	b;

	r = (double)x / (WIDTH - 1);
	g = (double)y / (HEIGHT - 1);
	b = 0.0;
	return (ft_create_trgb(0, r, g, b));
}
