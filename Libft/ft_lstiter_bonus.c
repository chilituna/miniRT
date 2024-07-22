/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:58:26 by aarponen          #+#    #+#             */
/*   Updated: 2023/06/01 16:26:20 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>

void	ft_add1(void *data)
{
	int *ptr = (int *)data;
	*ptr = *ptr + 1;
}
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		f(lst->content);
		lst = tmp;
	}
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

	ft_lstiter(node1, &ft_add1);
	printf("%d\n", *(int *)node1->content);
	printf("%d\n", *(int *)node1->next->content);
	free(node2);
	free(node1);
	return (0);
}*/
