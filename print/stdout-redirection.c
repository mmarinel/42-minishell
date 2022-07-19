/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout-redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:34:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 17:39:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	redirector(t_stdout_to_dump opcode)
{
	static int	stdout_clone = -1;
	static int	fd_stdout_dump_file = -1;

	if (opcode == STDOUT_2_DUMP)
	{
		stdout_clone = dup(STDOUT_FILENO);
		fd_stdout_dump_file = ft_open(
			get_stdout_dump_file_name(),
			O_CREAT | O_WRONLY | O_TRUNC, 0777,
			e_true
		);
		dup2(fd_stdout_dump_file, STDOUT_FILENO);
	}
	else if (opcode == STDOUT_RESTORE)
	{
		printf("cur stdout_clone is %d\n", stdout_clone);
		dup2(stdout_clone, STDOUT_FILENO);
		close(fd_stdout_dump_file);
	}
}
