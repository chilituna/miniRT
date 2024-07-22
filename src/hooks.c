/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:34:50 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:16:49 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Close the window with ESC
int	ft_key_handle(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_free_all(data);
		exit(0);
	}
	return (0);
}

// Close the window when clicking the red cross
int	ft_mouse_quit(t_data *data)
{
	ft_free_all(data);
	exit(0);
}
