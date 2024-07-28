/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:04:39 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/28 15:29:29 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_error(char *str, t_data *data)
{
	printf("Error: %s", str);
	ft_free_all(data);
	exit(1);
}

void	ft_parsing_error(char *str, t_data *data, char *line)
{
	free(line);
	line = NULL;
	ft_error(str, data);
}


