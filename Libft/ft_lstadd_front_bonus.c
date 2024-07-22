/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:33:20 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/31 15:58:54 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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

	printf("%d\n", *(int *)node1->content);
	printf("%d\n", *(int *)node1->next->content);

	int content3 = 1;
	t_list *node3 = ft_lstnew(&content3);
	ft_lstadd_front(&node1, node3);
	
	printf("%d\n", *(int *)node1->content);
	printf("%d\n", *(int *)node1->next->content);
	printf("%d\n", *(int *)node1->next->next->content);

	free (node1->next->next);
	free (node1->next);
	free (node1);
	return (0);
}*/
