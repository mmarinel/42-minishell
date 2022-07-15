/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:51:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 14:51:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static size_t	byteshift_update(char *line, size_t cur_byte_shift);

//* end of static declarations //


size_t	printer(t_print_opcode opcode)
{
	static size_t	stdout_byte_shift = 0;
	int				dump_file_fd;
	// int				stdout_clone;
	// int				stderr_clone;
	char			*line;

	if (opcode == GET_STDOUT_BYTE_SHIFT)
	{
		// printf("byte_shift is: %zu\n", stdout_byte_shift);
		return (stdout_byte_shift);
	}
	else
	{
		// stdout_clone = dup(STDOUT_FILENO);
		// stderr_clone = dup(STDERR_FILENO);
		dump_file_fd = open(".stdout-dump", O_RDONLY, 0777);
		// dup2(dump_file_fd, STDOUT_FILENO);
		// dup2(dump_file_fd, STDERR_FILENO);
		stdout_byte_shift = 0;
		while (e_true)
		{
			line = get_next_line(dump_file_fd, BUFFER_SIZE);
			if (line == NULL)
				break ;
			stdout_byte_shift = byteshift_update(line, stdout_byte_shift);
			ft_printf("%s", line);
			free(line);
		}
		// dup2(stdout_clone, STDOUT_FILENO);
		// dup2(stderr_clone, STDERR_FILENO);
		// close(dump_file_fd);
		unlink(".stdout-dump");
		return ((size_t)-1);
	}
}

static size_t	byteshift_update(char *line, size_t cur_byte_shift)
{
	size_t	offset;

	offset = 0;
	// printf("line[offset] = %c\n", line[offset]);
	while (line[offset])
	{
		// printf("line[offset] = %c", line[offset]);
		// fflush(stdout);
		if (line[offset] == '\n')
		{
			// printf("BBBOOOOO\n");
			cur_byte_shift = 0;
		}
		else
		{
			// printf("line[offset] = %c", line[offset]);
			// fflush(stdout);
			cur_byte_shift += 1;
		}
			// cur_byte_shift += 1;
		offset++;
	}
	return (cur_byte_shift);
}
