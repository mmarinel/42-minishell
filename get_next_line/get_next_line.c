// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_next_line.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/01/23 16:07:21 by mmarinel          #+#    #+#             */
// /*   Updated: 2022/06/18 18:48:45 by mmarinel         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "get_next_line.h"

// static char		*get_next_line_rec(int fd, t_fd_buffer *buf_handle);

// static t_bool	gnl_buffer_read_from_file(t_fd_buffer *buf_handle, int fd);
// static t_bool	gnl_get_line_from_buffer(t_fd_buffer *buf_handle, char **str);
// static int		find_new_line(char *str, int offset, int len, t_bool *nl_found);

// char	*get_next_line(int fd, int buffer_size)
// {
// 	static t_fd_buffer	buf_handle = (t_fd_buffer){NULL, BUFFER_SIZE, 0};

// 	if ((fd < 0 || fd > OPEN_MAX) || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	if (buf_handle.offset == 0)
// 	{
// 		if (buffer_size < 0)
// 			buf_handle.buffer_size = BUFFER_SIZE;
// 		else
// 			buf_handle.buffer_size = buffer_size;
// 	}
// 	return (get_next_line_rec(fd, &buf_handle));
// }

// static char	*get_next_line_rec(int fd, t_fd_buffer *buf_handle)
// {
// 	char		*str;
// 	t_bool		nl_found;

// 	if (buf_handle->offset == 0)
// 	{
// 		if (e_false == gnl_buffer_read_from_file(buf_handle, fd))
// 			return (NULL);
// 	}
// 	nl_found = gnl_get_line_from_buffer(buf_handle, &str);
// 	if (buf_handle->offset == 0 || buf_handle->buf[buf_handle->offset] == '\0')
// 	{
// 		free(buf_handle->buf);
// 		if (buf_handle->offset == 0 && !nl_found)
// 		{
// 			buf_handle->buffer_size = buf_handle->buffer_size + 5;
// 			return (gnl_strjoin(str, get_next_line_rec(fd, buf_handle),
// 					e_true, e_true));
// 		}
// 		buf_handle->offset = 0;
// 	}
// 	return (str);
// }

// static t_bool	gnl_buffer_read_from_file(t_fd_buffer *buf_handle, int fd)
// {
// 	buf_handle->buf = (char *) malloc
// 		(
// 			(buf_handle->buffer_size + 1) * sizeof(char)
// 			);
// 	gnl_memset(buf_handle->buf, '\0', buf_handle->buffer_size + 1);
// 	if (read(fd, buf_handle->buf, buf_handle->buffer_size) <= 0)
// 	{
// 		free(buf_handle->buf);
// 		return (e_false);
// 	}
// 	return (e_true);
// }

// static t_bool	gnl_get_line_from_buffer(t_fd_buffer *buf_handle, char **str)
// {
// 	t_bool	nl_found;
// 	int		line_len;
// 	int		buffer_start;
// 	int		i;

// 	nl_found = e_false;
// 	buffer_start = buf_handle->offset;
// 	i = find_new_line(buf_handle->buf,
// 			buf_handle->offset,
// 			buf_handle->buffer_size,
// 			&nl_found);
// 	if (buf_handle->buf[i] == '\0')
// 		line_len = i - buf_handle->offset;
// 	else
// 		line_len = i - buf_handle->offset + 1;
// 	if (i == buf_handle->buffer_size - 1
// 		|| buf_handle->buf[i] == '\0')
// 		buf_handle->offset = 0;
// 	else
// 		buf_handle->offset = i + 1;
// 	gnl_strlcpy(str, buf_handle->buf + buffer_start, line_len);
// 	return (nl_found);
// }

// static int	find_new_line(char *str, int offset, int len, t_bool *nl_found)
// {
// 	int	i;

// 	i = offset;
// 	while (i < len)
// 	{
// 		if (str[i] == '\n')
// 			*nl_found = e_true;
// 		if (str[i] == '\n' || str[i] == '\0')
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }
