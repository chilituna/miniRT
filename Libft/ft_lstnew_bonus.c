/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen aarponen@student.42berlin.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:05:33 by aarponen          #+#    #+#             */
/*   Updated: 2023/06/01 18:41:41 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
int main(void)
{

	int content1 = 42;
	t_list *node1 = ft_lstnew(&content1);
	char content2[] = "Berlin";
	t_list *node2 = ft_lstnew(content2);

	printf("%d\n", *(int *)node1->content);
	printf("%s\n", (char *)node2->content);
	free (node1);
	free (node2);
	return (0);
}*/
