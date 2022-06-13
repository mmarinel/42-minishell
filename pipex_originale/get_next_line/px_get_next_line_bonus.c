/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_get_next_line_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:47:01 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 14:45:41 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char				*buf;
	static int				offset;
	static ssize_t			bytes_read;
	char					*str;
	int						nl_found;

	nl_found = 0;
	str = NULL;
	while (!nl_found)
	{
		if (!offset)
			ft_get_line_initialize_buffer(&buf, &bytes_read, fd);
		if (!buf || bytes_read < 0)
			return (ft_get_line_output(&str, &buf, ERROR));
		else if (bytes_read == 0)
			return (ft_get_line_output(&str, &buf, SUCCESS_DISCARD_BUFFER));
		offset = (offset + ft_get_line(buf + offset,
					BUFFER_SIZE - offset, &nl_found, &str)) % BUFFER_SIZE;
		if ((!offset && nl_found) || (buf[offset] == '\0'))
			return (ft_get_line_output(&str, &buf, SUCCESS_DISCARD_BUFFER));
	}
	return (ft_get_line_output(&str, &buf, SUCCESS_KEEP_BUFFER));
}

unsigned int	ft_get_line(char *buf, unsigned int max_len,
					int *nl_found, char **line)
{
	unsigned long long	i;
	char				*join_line;

	i = 0;
	while (i < max_len && buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (i < max_len && buf[i] == '\n')
	{
		*nl_found = 1;
		i++;
	}
	join_line = gnl_strjoin(*line, buf, i);
	ft_free(line);
	*line = join_line;
	return (i);
}

char	*ft_get_line_output(char **str, char **buf, int exit_mode)
{
	if (exit_mode == SUCCESS_DISCARD_BUFFER || exit_mode == ERROR)
	{
		ft_free(buf);
		if (exit_mode == ERROR)
			ft_free(str);
	}
	return (*str);
}

void	ft_get_line_initialize_buffer(char **buf, ssize_t *bytes_read, int fd)
{
	ft_free(buf);
	*buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	ft_memset(*buf, '\0', BUFFER_SIZE + 1);
	if (*buf)
		*bytes_read = read(fd, *buf, BUFFER_SIZE);
}

void	ft_free(char **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	if (ptr)
		*ptr = NULL;
}
