/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:31:24 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/17 15:57:51 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <fcntl.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}
/*
int	main(void)
{
	char	s[] = "silvissii";
	int		fd;

	fd = open("test_putstr.txt", O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}
	ft_putendl_fd(s, fd);
	close(fd);
	return(0);
}*/
