/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:45:54 by aarponen          #+#    #+#             */
/*   Updated: 2023/05/31 18:23:25 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (*lst == NULL)
		*lst = new;
	else
	{
		p = ft_lstlast(*lst);
		p->next = new;
	}
}
/*
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next != NULL)
		p = p->next;
	return (p);
}

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

	int content3 = 4;
	t_list *node3 = ft_lstnew(&content3);
	ft_lstadd_back(&node1, node3);
	
	printf("%d\n", *(int *)node1->content);
	printf("%d\n", *(int *)node1->next->content);
	printf("%d\n", *(int *)node1->next->next->content);

	free (node1->next->next);
	free (node1->next);
	free (node1);
	return (0);
}*/
