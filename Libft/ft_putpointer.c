/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:00:46 by aarponen          #+#    #+#             */
/*   Updated: 2023/10/28 21:08:21 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long nb)
{
	int		len;

	len = 0;
	if (nb >= 16)
	{
		len += ft_putptr(nb / 16);
		len += ft_putptr(nb % 16);
	}
	else
	{
		if (nb < 10)
			len += ft_putchar(nb + '0');
		else
			len += ft_putchar(nb - 10 + 'a');
	}
	return (len);
}

int	ft_putpointer(unsigned long ptr)
{
	int			len;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	len = 0;
	len += ft_putchar('0');
	len += ft_putchar('x');
	len += ft_putptr(ptr);
	return (len);
}
