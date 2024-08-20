/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:26:19 by s.veselova        #+#    #+#             */
/*   Updated: 2024/08/20 16:33:58 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	ft_strendswith(const char *str, const char *suffix)
{
	size_t	str_len;
	size_t	suffix_len;

	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return (0);
	return (ft_strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0);
}

// Helper function to check and update required parameters
// Check if there's only one ambient/camera/light input
static int	ft_check_required_params(char first_char, int *has_ambient,
		int *has_camera, int *has_light)
{
	if (first_char == 'A')
	{
		if (*has_ambient)
			return (0);
		*has_ambient = 1;
	}
	else if (first_char == 'C')
	{
		if (*has_camera)
			return (0);
		*has_camera = 1;
	}
	else if (first_char == 'L')
	{
		if (*has_light)
			return (0);
		*has_light = 1;
	}
	return (1);
}

// Helper function to modularise a long func below
static int	ft_process_required_params(char *line,
		int *has_ambient, int *has_camera, int *has_light)
{
	if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
	{
		if (!ft_check_required_params(line[0], has_ambient,
				has_camera, has_light))
		{
			return (0);
		}
	}
	return (1);
}

// Function to parse the file contents
static int	ft_parse_file_contents(int fd, t_data *data)
{
	char	*line;
	int		has_ambient;
	int		has_camera;
	int		has_light;

	has_ambient = 0;
	has_camera = 0;
	has_light = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_process_required_params(line, &has_ambient,
				&has_camera, &has_light))
		{
			free(line);
			return (0);
		}
		ft_parsing(line, data);
		free(line);
	}
	return (has_ambient && has_camera && has_light);
}

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
	int	fd;

	if (!ft_strendswith(file, ".rt"))
		ft_error("Invalid file extension. Only .rt files are allowed.\n", data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Could not open file\n", data);
	if (!ft_parse_file_contents(fd, data))
	{
		close(fd);
		ft_error("Missing or duplicate A, C, or L parameters\n", data);
	}
	close(fd);
	return (0);
}
