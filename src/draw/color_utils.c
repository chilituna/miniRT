/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sveselov <sveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:59:12 by sveselov          #+#    #+#             */
/*   Updated: 2024/08/20 17:59:47 by sveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_clamp_color(t_color *color)
{
	color->r = fminf(color->r, 255);
	color->g = fminf(color->g, 255);
	color->b = fminf(color->b, 255);
}
