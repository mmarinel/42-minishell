/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:51:54 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 20:16:13 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "prompt/prompt.h"

// TODO :-> put error where exit_shell is (put error will also use exit_shell)
char	*shell_read( char *const envp[])
{
	char	*command;

	printf("\1");
	command = ft_readline
		(
			ft_strjoin(
				get_current_working_directory(),
				ft_strjoin(RESET, "\2", e_false, e_false),
				e_true, e_true),
			e_true
			);
	printf("line read: %s\n", command);
	return (command);
	if (envp)
		;
}
