/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:24 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/31 16:28:35 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*p;

	if (lst == NULL)
		return (0);
	count = 0;
	p = lst;
	while (p != 0)
	{
		count++;
		p = p->next;
	}
	return (count);
}
/*
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int main(void)
{
	int content1 = 2;
	t_list *node1 = ft_lstnew(&content1);
	int content2 = 3;
	t_list *node2 = ft_lstnew(&content2);
	node1->next = node2;

	printf("%d\n", ft_lstsize(node1));
	free (node2);
	free (node1);
	return (0);
}*/
