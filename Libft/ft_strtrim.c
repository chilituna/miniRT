/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:23:08 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/28 13:44:38 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/*size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

*/

char	*ft_newstr(char *str, char const *s1, size_t end, size_t start)
{
	size_t	i;

	i = 0;
	while (i <= end - start)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_strchr(set, (int)s1[start]) && s1[start])
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)s1[end]))
		end--;
	str = malloc(sizeof(char) * (end - start + 2));
	if (str == NULL)
		return (NULL);
	return (ft_newstr(str, s1, end, start));
}
/*
int	main(void)
{
	const char	*s1;
	const char	*set;
	char		*result;

	s1 = "";
	set = "";
	result = ft_strtrim(s1, set);
	printf("%s\n", result);
	free(result);
	return (0);
}*/
