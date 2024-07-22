/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:08:33 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/05 10:10:06 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		p[i] = (char) c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	s[] = "hello";
	int		c = 'x';
	size_t	n = 3;

	printf("%s\n", s);
	ft_memset(s, c, n);
	printf("%s\n", s);
	return (0);
}*/
