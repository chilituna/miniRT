/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:31:40 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/21 14:19:03 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_parse_integer(const char **str)
{
	int	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}

	return (result);
}

float	ft_parse_fraction(const char **str)
{
	float	result;
	float	frac;

	result = 0.0f;
	frac = 1.0f;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result = result * 10.0f + (**str - '0');
			frac *= 10.0f;
			(*str)++;
		}
	}
	return (result / frac);
}

// Convert a string to a floating point number
float	ft_atof(const char *str)
{
	float	result;
	int		integer_part;
	float	fractional_part;
	int		sign;

	result = 0.0f;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	integer_part = ft_parse_integer(&str);
	fractional_part = ft_parse_fraction(&str);
	result = (float)integer_part + fractional_part;
	return (result * sign);
}
