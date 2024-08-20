/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sveselov <sveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:42:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/08/20 18:26:52 by sveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i++] = '\n';
	}
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		res = ft_free_gnl(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_next(buffer);
	return (line);
}

// char	*pre_ft_strjoin(char *line, char *temp_buffer)
// {
// 	char	*str;

// 	if (temp_buffer[0] == '\0' && !line)
// 	{
// 		free(temp_buffer);
// 		return (NULL);
// 	}
// 	if (!line)
// 	{
// 		line = (char *)malloc(sizeof(char) * 1);
// 		if (!line)
// 		{
// 			free(temp_buffer);
// 			return (NULL);
// 		}
// 		line[0] = '\0';
// 	}
// 	str = ft_strjoin(line, temp_buffer);
// 	if (!str)
// 		free(temp_buffer);
// 	free(line);
// 	return (str);
// }

// char	*go_to_next_line(char *line)
// {
// 	char	*next_line;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (line[i] != '\n' && line[i])
// 		i++;
// 	if (line[i] == '\0')
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	while (line[i + j])
// 		j++;
// 	next_line = ft_substr(line, i + 1, j);
// 	if (!next_line)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	free(line);
// 	return (next_line);
// }

// char	*copy_new_line(char *line)
// {
// 	char	*new_line;
// 	int		i;

// 	i = 0;
// 	while (line[i] != '\n' && line[i])
// 		i++;
// 	new_line = ft_substr(line, 0, i + 1);
// 	if (!new_line)
// 	{
// 		free(line);
// 		line = NULL;
// 		return (NULL);
// 	}
// 	return (new_line);
// }

// char	*ft_read_line(int fd, char *reading_line)
// {
// 	int		read_bytes;
// 	char	*temp_buffer;

// 	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!temp_buffer)
// 		return (NULL);
// 	read_bytes = 1;
// 	while (!ft_strchr(reading_line, '\n') && read_bytes != 0)
// 	{
// 		read_bytes = read(fd, temp_buffer, BUFFER_SIZE);
// 		if (read_bytes == -1)
// 		{
// 			if (reading_line)
// 				free(reading_line);
// 			free(temp_buffer);
// 			return (NULL);
// 		}
// 		temp_buffer[read_bytes] = '\0';
// 		reading_line = pre_ft_strjoin(reading_line, temp_buffer);
// 		if (!reading_line)
// 			return (NULL);
// 	}
// 	free(temp_buffer);
// 	return (reading_line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*reading_line;
// 	char		*new_line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	reading_line = ft_read_line(fd, reading_line);
// 	if (!reading_line)
// 		return (NULL);
// 	if (reading_line[0] == '\0')
// 	{
// 		free(reading_line);
// 		reading_line = NULL;
// 		return (NULL);
// 	}
// 	new_line = copy_new_line(reading_line);
// 	if (!new_line)
// 		return (NULL);
// 	reading_line = go_to_next_line(reading_line);
// 	return (new_line);
// }
// ssize_t custom_read(int fd, void *buf, size_t count)
// {
// 	if (fd && buf && count > 0)
//     	return (-1);
// 	elset_fd_node			*current_fd;
// 		return (0);
// }
// void* custom_malloc(size_t size)
// {
//     if (size > 0)
// 		return NULL;
// 	else
// 		return (ft_strdup(""));
// }
// int	main(void)
// {
// 	char	*line;
// 	int		line_nbr;
// 	int		test_file;
// 	// test_file = open("test.txt", O_RDONLY);
// 	test_file = 0;
// 	line_nbr = 1;
// 	while (line_nbr <= 3)
// 	{
// 		line = get_next_line(test_file);
// 		if (!line)
// 			return (0);
// 		printf("Line %d: %s", line_nbr, line);
// 		free(line);
// 		line = NULL;
// 		line_nbr++;
// 	}
// 	close(test_file);
// 	return (0);
// }
