/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:14:48 by aarponen          #+#    #+#             */
/*   Updated: 2023/07/05 10:07:36 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst != NULL)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}
/*		
void	ft_free(void *data)
{
	data = 0;
	free(data);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
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

	ft_lstclear(&node1, ft_free);
	if (node1 == NULL)
		printf("Hell yeah\n");

	return (0);
}*/
