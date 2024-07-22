/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:04:39 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 15:21:56 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_error(char *str)
{
	printf("Error: %s", str);
	exit(1);
}

void	ft_error_and_free(char *str, char **arr)
{
	ft_free_array(arr);
	ft_error(str);
}

void	ft_error_and_free_2(char *str, char **arr, char **arr2)
{
	ft_free_array(arr);
	ft_free_array(arr2);
	ft_error(str);
}
