/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_command_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:23:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 15:23:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_children.h"

static void	px_get_cmd_inital(t_cmd **cmd, char const *argv[]);

/**
 * @brief parses the argv string and builds the list of shell commands
 * with their respective input/ouptut file paths
 * 
 * @param cmd pointer to the first element of the list of shell commands
 * @param argc length of the argv string
 * @param argv the input string to the pipex program
 * @return int the number of shell commands in the pipe chain
 */
void	px_get_cmds(t_cmd **cmd, int argc, char const *argv[])
{
	int	i;

	px_get_cmd_inital(cmd, argv);
	i = 2;
	while (i < argc)
	{
		(*cmd)->next = (t_cmd *) px_malloc(sizeof(t_cmd));
		(*cmd)->next->prev = (*cmd);
		(*cmd) = (*cmd)->next;
		(*cmd)->cmd = (char *) argv[i++];
		if (i == argc - 1)
		{
			(*cmd)->file = (char *) argv[i++];
			(*cmd)->next = NULL;
			(*cmd)->is_last = e_true;
		}
		else
		{
			pipe((*cmd)->outpipe);
			(*cmd)->is_last = e_false;
		}
		(*cmd)->is_first = e_false;
		(*cmd)->append = e_false;
	}
}

static void	px_get_cmd_inital(t_cmd **cmd, char const *argv[])
{
	*cmd = (t_cmd *) px_malloc(sizeof(t_cmd));
	(*cmd)->file = (char *) argv[0];
	(*cmd)->cmd = (char *) argv[1];
	(*cmd)->is_first = e_true;
	(*cmd)->is_last = e_false;
	if (pipe((*cmd)->outpipe) < 0)
		px_error_handler(0, NULL, e_false);
	(*cmd)->prev = NULL;
	(*cmd)->append = e_false;
}
