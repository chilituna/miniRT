/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:38:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/18 17:32:07 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_check_identifier(char *line, t_data *data)
{
	if (line[0] == 'A')
	{
		ft_parse_ambient(line, data);
	}
	else if (line[0] == 'C')
	{
		ft_parse_camera(line, data);
	}
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
void	ft_parsing(int fd, char *line, t_data *data)
{
	data->line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (data->line_count == 0)
				ft_error("Empty file\n", data);
			break ;
		}
		data->line_count++;
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			continue ;
		}
		else
			ft_check_identifier(line, data);
		free(line);
	}
}
