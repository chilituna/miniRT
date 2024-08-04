/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:04:27 by s0nia             #+#    #+#             */
/*   Updated: 2024/08/04 21:31:07 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_calculate_diffuse_lighting(t_vector *normal, t_vector *light_dir)
{
	float dot_product = ft_dot(normal, light_dir);
	return fmaxf(0.0f, dot_product);
}
