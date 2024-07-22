/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:10:31 by aarponen          #+#    #+#             */
/*   Updated: 2023/10/28 21:42:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	ft_check_format(const char *input, va_list args)
{
	int	len;

	len = 0;
	if (*input == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (*input == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (*input == 'p')
		len += ft_putpointer(va_arg(args, unsigned long));
	else if (*input == 'd' || *input == 'i')
		len += ft_putint(va_arg(args, int));
	else if (*input == 'u')
		len += ft_putunsigned(va_arg(args, unsigned int));
	else if (*input == 'x' || *input == 'X')
		len += ft_puthex(va_arg(args, unsigned int), input);
	else if (*input == 'f')
		len += ft_putfloat(va_arg(args, double));
	return (len);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		len;

	if (input == 0)
		return (-1);
	len = 0;
	va_start(args, input);
	while (*input != '\0')
	{
		if (*input == '%')
		{
			input++;
			if (ft_strchr("cspdiuxXf", *input))
				len += ft_check_format(input, args);
			else if (*input == '%')
				len += ft_putchar('%');
		}
		else
			len = len + ft_putchar(*input);
		input++;
	}
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	char			c;
// 	char			*str;
// 	int				i;
// 	unsigned int	u;
// 	char			*ptr;

// 	c = 'A';
// 	str = "";
// 	i = -2147483648;
// 	u = 4294967295;
// 	ptr = &c;
// 	ft_printf("\n%d\n", ft_printf("Hello %c! This is %s.\n", c, str));
// 	printf("\n%d\n", printf("Hello %c! This is %s.\n", c, str)); 
// 	ft_printf("\n%d\n", ft_printf("The chosen ones are %d and %u.\n", i, u));
// 	printf("\n%d\n", printf("The chosen ones are %d and %u.\n", i, u));
// 	ft_printf("\n%d\n", ft_printf("Also known as: %x and %X\n", u, u));
// 	printf("\n%d\n", printf("Also known as: %x and %X\n", u, u));
// 	ft_printf("\n%d\n", ft_printf("You live in %p\n", ptr));
// 	printf("\n%d\n", printf("You live in %p\n", ptr));
// 	ft_printf("\n%d\n", ft_printf(0));
// 	printf("\n%d\n",  printf(0));
// 	return (0);
// }
