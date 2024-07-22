/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:01:12 by aarponen          #+#    #+#             */
/*   Updated: 2023/10/28 21:01:23 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

double	ft_decimals(const char *str, int i)
{
	double	factor;
	double	dec;

	factor = 0.1;
	dec = 0.0;
	i++;
	while (ft_isdigit(str[i]))
	{
		dec = dec + (str[i] - '0') * factor;
		factor *= 0.1;
		i++;
	}
	return (dec);
}

double	ft_atod(const char *str)
{
	double	nb;
	double	decimal;
	int		i;
	int		sign;

	nb = 0.0;
	decimal = 0.0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		decimal = ft_decimals(str, i);
	return (sign * (nb + decimal));
}
// int	main(void)
// {
// 	const char	*str;

// 	str = "-02.123456789";
// 	printf("%f\n", ft_atod(str));
// 	return (0);
// }
