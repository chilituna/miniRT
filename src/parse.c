/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:38:19 by aarponen          #+#    #+#             */
/*   Updated: 2024/07/22 19:26:07 by aarponen         ###   ########.fr       */
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

// Parse the scene file line by line:
void	ft_parsing(int fd, char *line, t_data *data)
{
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == 'A')
			ft_parse_ambient(line, data);
		else if (line[0] == 'C')
			ft_parse_camera(line, data);
		else if (line[0] == 'L')
			ft_parse_light(line, data);
		// else if (line[0] == 's' && line[1] == 'p')
		// 	ft_parse_sphere(line, &data->sphere);
		// else if (line[0] == 'p' && line[1] == 'l')
		// 	ft_parse_plane(line, &data->plane);
		// else if (line[0] == 'c' && line[1] == 'y')
		// 	ft_parse_cylinder(line, &data->cylinder);
		else if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			continue ;
		}
		else
			ft_error("Invalid identifier\n", data);
		free(line);
	}
}
