/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spanfilo <spanfilo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 10:03:25 by spanfilo      #+#    #+#                 */
/*   Updated: 2024/12/17 13:59:30 by sveta         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	new_line_char(char *buffer)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(buffer);
	i = 0;
	while (i < len && buffer[i] != '\n')
		i++;
	return (i);
}

static int	divide_inside_buffer(char *buffer, char **line, size_t i)
{
	char	*temp;
	char	*left_buffer;

	left_buffer = malloc(i + 2);
	if (!left_buffer)
	{
		buffer[0] = '\0';
		return (1);
	}
	ft_strlcpy(left_buffer, buffer, i + 2);
	temp = ft_strjoin(*line, left_buffer);
	if (!temp)
	{
		buffer[0] = '\0';
		free(left_buffer);
		return (1);
	}
	if (*line != NULL)
		free(*line);
	*line = temp;
	ft_strlcpy(buffer, buffer + i + 1, ft_strlen(buffer) - i);
	free(left_buffer);
	return (0);
}

static int	copy_buffer(char *buffer, char **line)
{
	char	*temp;

	temp = ft_strjoin(*line, buffer);
	if (!temp)
	{
		buffer[0] = '\0';
		return (1);
	}
	if (*line != NULL)
		free(*line);
	*line = temp;
	buffer[0] = '\0';
	return (0);
}

static int	divide_line_buffer(char *buffer, char **line)
{
	size_t		i;
	size_t		len;

	len = ft_strlen(buffer);
	i = new_line_char(buffer);
	if (i < len - 1)
		return (divide_inside_buffer(buffer, line, i));
	else
		return (copy_buffer(buffer, line));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			bytes_read;

	line = NULL;
	bytes_read = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read == 0)
				break ;
			if (bytes_read < 0)
				return (free_mem(&line));
			buffer[bytes_read] = '\0';
		}
		if (divide_line_buffer(buffer, &line) == 1)
			return (free_mem(&line));
		if (line && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	return (line);
}
