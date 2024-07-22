/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:53:56 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/05 10:08:36 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"
/*
char	ft_change(unsigned int index, char c)
{
	return (c + (char)index);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*arr;

	len = 0;
	while (s[len])
		len++;
	arr = malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
/*
int	main(void)
{
	char const	*s;
	char		*arr;

	s = "Hello";
	arr = ft_strmapi(s, ft_change);
	printf("%s\n", arr);
	free(arr);
	return (0);
}*/
