/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:34:57 by s.veselova        #+#    #+#             */
/*   Updated: 2024/08/15 21:40:06 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Close the window with ESC
int	ft_key_handle(int keysym, t_data *data)
{
	if (keysym == tokEscape)
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
