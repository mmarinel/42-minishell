/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 10:51:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 09:30:11 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static size_t	byteshift_update(char *line, size_t cur_byte_shift);

//* end of static declarations //


size_t	printer(t_print_opcode opcode)
{
	static size_t	stdout_byte_shift = 0;
	char			*dump_file_name;
	int				dump_file_fd;
	char			*line;

	if (opcode == GET_STDOUT_BYTE_SHIFT)
	{
		return (stdout_byte_shift);
	}
	else
	{
		dump_file_name = get_stdout_dump_file_name();
		dump_file_fd = ft_open(dump_file_name, O_RDONLY, 0777,
							e_false);
		stdout_byte_shift = 0;
		while (e_true)
		{
			line = get_next_line(dump_file_fd, BUFFER_SIZE);
			if (line == NULL)
				break ;
			stdout_byte_shift = byteshift_update(line, stdout_byte_shift);
			free(line);
		}
		close(dump_file_fd);
		ft_unlink(dump_file_name, e_true);
		return ((size_t)-1);
	}
}

static size_t	byteshift_update(char *line, size_t cur_byte_shift)
{
	size_t	offset;

	offset = 0;
	while (line[offset])
	{
		if (line[offset] == '\n')
		{
			cur_byte_shift = 0;
		}
		else
		{
			cur_byte_shift += 1;
		}
		offset++;
	}
	return (cur_byte_shift);
}
