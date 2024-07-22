/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:48:03 by aarponen          #+#    #+#             */
/*   Updated: 2023/10/28 21:08:10 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_converthex(unsigned int nb, const char *input)
{
	int	len;

	len = 0;
	if (nb >= 16)
	{
		len += ft_converthex(nb / 16, input);
		len += ft_converthex(nb % 16, input);
	}
	else
	{
		if (nb < 10)
			len += ft_putchar(nb + '0');
		else
		{
			if (*input == 'x')
				len += ft_putchar(nb - 10 + 'a');
			if (*input == 'X')
				len += ft_putchar(nb - 10 + 'A');
		}
	}
	return (len);
}

int	ft_puthex(unsigned int nb, const char *input)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		return (ft_converthex(nb, input));
}
