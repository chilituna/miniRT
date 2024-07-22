/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:08:05 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/10 14:37:04 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*new_s;
	size_t		len;
	size_t		i;

	len = ft_strlen(s);
	new_s = malloc((len +1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
/*
int	main(void)
{
	const char	*s = "moroo";
	char		*p;
	char		*p2;

	p = ft_strdup(s);
	printf("%s\n", p);
	free(p);
	p2 = strdup(s);
	printf("%s\n", p);
	free(p2);
	return (0);
}*/
