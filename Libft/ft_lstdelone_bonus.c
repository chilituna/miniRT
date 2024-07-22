/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:27:48 by aarponen          #+#    #+#             */
/*   Updated: 2023/06/01 14:38:02 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>

/*void	ft_free(void *data)
{
	data = 0;
	free(data);
}
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
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

	ft_lstdelone(node2, ft_free);
	if (node2 == NULL)
		printf("Hell yeah\n");

	free (node1);
	return (0);
}*/
