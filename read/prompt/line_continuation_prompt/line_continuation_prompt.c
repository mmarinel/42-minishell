/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_continuation_prompt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 11:00:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_continuation_prompt.h"

static void	read_until_complete(char **continuation,
			int line_channel[2], int line_size_channel[2]);
static void	read_until_complete_rec(char **old);
static void	send_command_to_parent(char *command,
			int line_channel[2], int line_size_channel[2]);

// * end of static declarations //


void	line_continuation_prompt(t_prompt_behav opcode,
			int line_channel[2], int line_size_channel[2])
{
	static char	*continuation = NULL;

	if (opcode == KILL)
	{
		send_command_to_parent(continuation,
			NULL, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, line_completion_prompt_sig_handler);
		close(line_channel[0]);
		close(line_size_channel[0]);
		if (opcode == COMPLETE_LINE)
		{
			read_until_complete(&continuation,
				line_channel, line_size_channel);
			exit(EXIT_SUCCESS);
		}
	}
}

static void	read_until_complete(char **continuation,
			int line_channel[2], int line_size_channel[2])
{
	read_until_complete_rec(continuation);
	send_command_to_parent(*continuation,
		line_channel, line_size_channel);
}

	// if (*continuation)
	// {
	// 	continuation_len = ft_strlen(*continuation);
	// }
	// else
	// {
	// 	continuation_len = 1;
	// 	*continuation = ft_strcpy(NULL, "", 0);
	// }
	// write(line_size_channel[1], &continuation_len, sizeof(continuation_len));
	// write(line_channel[1], *continuation, continuation_len * sizeof(char));
	// free(*continuation);
	// close_pipe(line_channel);
	// close_pipe(line_size_channel);

static void	read_until_complete_rec(char **old)
{
	char	*continuation;

	continuation = readline("> ");
	if (!continuation)
		return ;
	else if (*continuation == '\0')
		read_until_complete_rec(old);
	else
	{
		*old = ft_strjoin(*old, continuation, e_true, e_true);
		{
			if (e_true == ft_pending_pipe(*old)
				|| e_true == ft_pending_logical_op(*old))
				read_until_complete_rec(old);
			else
				return ;
		}
	}
}

static void	send_command_to_parent(char *command,
			int line_channel[2], int line_size_channel[2])
{
	static int	line_chl[2];
	static int	line_size_chl[2];
	size_t		final_command_len;

	if (line_channel && line_size_channel)
	{
		line_chl[0] = line_channel[0];
		line_chl[1] = line_channel[1];
		line_size_chl[0] = line_size_channel[0];
		line_size_chl[1] = line_size_channel[1];
	}
	if (command)
	{
		final_command_len = ft_strlen(command);
	}
	else
	{
		final_command_len = 1;
		command = ft_strcpy(NULL, "", 0);
	}
	write(line_size_chl[1], &final_command_len, sizeof(final_command_len));
	write(line_chl[1], command, final_command_len * sizeof(char));
	free(command);
	close_pipe(line_chl);
	close_pipe(line_size_chl);
}
