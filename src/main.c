/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:38:01 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/27 12:26:32 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argv;
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Failed to allocate memory for data\n");
		return (1);
	}
	ft_init_data(data);
	ft_parse_scene(argv[1], data);
	ft_launch_mlx(data);
	return (0);
}
