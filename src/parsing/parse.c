/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:38:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/04 21:55:50 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Parse the scene file and store the data in the appropriate structs:
// A = Ambient lighting (only one)
// C = Camera (only one)
// L = Light (only one)
// sp = Sphere
// pl = Plane
// cy = Cylinder
// Check that all values are within the correct range and return 0 on success
// Exit with an error message and return 1 on failure
int	ft_parse_scene(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Could not open file\n", data);
	line = NULL;
	ft_parsing(fd, line, data);
	close(fd);
	return (0);
}

void	ft_check_identifier(char *line, t_data *data)
{
	if (line[0] == 'A')
	{
		printf("line: %s\n", line);
		ft_parse_ambient(line, data);
	}
	else if (line[0] == 'C')
	{
		ft_parse_camera(line, data);
		printf("line camera: %s\n", line);
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
