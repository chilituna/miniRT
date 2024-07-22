/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:52:58 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/05 10:09:54 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	ft_move(char *pd, char *ps, size_t n, int i)
{
	if (pd <= ps || pd >= (ps + n))
	{
		while (i < (int)n)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	else
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			pd[i] = ps[i];
			i--;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;

	if (!dest && !src)
		return (0);
	i = 0;
	ft_move((char *)dest, (char *)src, n, i);
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "123456";
	size_t	n = 3;

	printf("before: %s\n", src);
	ft_memmove(src + 3, src, n);
	printf("after: %s\n", src);
	return (0);
}*/
