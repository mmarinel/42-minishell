/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:51:54 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 16:55:06 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
# include "prompt/prompt.h"

// TODO :-> put error where exit_shell is (put error will also use exit_shell)
char	*shell_read( char *const envp[])
{
	char	*command;

	command = ft_readline(get_current_working_directory(), e_true);
	printf("line read: %s\n", command);
	return (command);
	if (envp)
		;
}
