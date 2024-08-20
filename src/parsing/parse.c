/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:38:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/20 16:30:43 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_check_identifier(char *line, t_data *data)
{
	if (line[0] == 'A')
		ft_parse_ambient(line, data);
	else if (line[0] == 'C')
		ft_parse_camera(line, data);
	else if (line[0] == 'L')
		ft_parse_light(line, data);
	else if (line[0] == 's' && line[1] == 'p')
		ft_parse_sphere(line, data);
	else if (line[0] == 'p' && line[1] == 'l')
		ft_parse_plane(line, data);
	else if (line[0] == 'c' && line[1] == 'y')
		ft_parse_cylinder(line, data);
	else
		ft_parsing_error("Invalid identifier\n", data, line);
}

// Parse the scene file line by line:
void	ft_parsing(char *line, t_data *data)
{
	if (line[0] == '\n' || line[0] == '#')
		return ;
	else
		ft_check_identifier(line, data);
}
