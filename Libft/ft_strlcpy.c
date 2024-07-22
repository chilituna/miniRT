/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:43:00 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/05 16:51:12 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
#include "libft.h"

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char			src[] = "rallaa!";
	char			dst[] = "heippa";
	unsigned int	size = 7;

	printf("%s\n", dst);
	printf("%d\n", ft_strlcpy(dst, src, size));
	printf("%s\n", dst);
	return (0);
}*/
