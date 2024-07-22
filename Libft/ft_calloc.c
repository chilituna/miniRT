/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:09:15 by aarponen          #+#    #+#             */
/*   Updated: 2023/06/06 18:33:12 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdint.h>
//#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*p;

	p = malloc(nmeb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmeb * size);
	return (p);
}
/*
int	main(void)
{
	size_t	nmeb = sizeof(int);
	size_t	size = 0;
	int		*arr = ft_calloc(nmeb, size);
	int		i = 0;

	if (size > 0)
	{
		while (i < 10)
		{
			printf("%d", arr[i]);
			i++;
		}
		printf("\n");
		while (i > 0)
		{
			arr[i] = i;
			i--;
		}
		while (i < 10)
		{
			printf("%d", arr[i]);
			i++;
		}
		printf("\n");
		free(arr);
	}
	return (0);
}*/
