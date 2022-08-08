/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_continuation_prompt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 15:06:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_continuation_prompt.h"

static void	read_until_complete_rec(char **command_ref, char *last);
static void	send_command_to_parent(char *command,
			int line_channel[2], int line_size_channel[2]);
t_status	here_doc_handling(char *last);

// * end of static declarations //


void	line_continuation_prompt(t_prompt_behav opcode, char *initial_command,
			int line_channel[2], int line_size_channel[2])
{
	static char	*command = NULL;
	static int	line_chl[2];
	static int	line_size_chl[2];

	if (opcode == KILL)
	{
		send_command_to_parent(command,
			line_chl, line_size_chl);
		exit(EXIT_FAILURE);
	}
	else
	{
		command = NULL;
		// printf("initial command is: %s\n", initial_command);
		clone_pipe(line_channel, line_chl);
		clone_pipe(line_size_channel, line_size_chl);
		close(line_chl[0]);
		close(line_size_chl[0]);
		signal(SIGINT, line_completion_prompt_sig_handler);
		read_until_complete_rec(&command, initial_command);
		send_command_to_parent(command, line_chl, line_size_chl);
		exit(EXIT_SUCCESS);
	}
}

static void	read_until_complete_rec(char **command_ref, char *last)
{
	char			*ret;
	char			*continuation;

	if (*command_ref)
		*command_ref = ft_strjoin(
			ft_strjoin(*command_ref, " ", e_true, e_false),
			last,
			e_true, e_false
		);
	else
		*command_ref = ft_strdup(last);
	// *command_ref = ft_strjoin(*command_ref, last, e_true, e_false);
	if (OK == here_doc_handling(last))
	{
		if (e_true == ft_pending_pipe(last)
			|| e_true == ft_pending_logical_op(last))
		{
			continuation = ft_readline("> ");
			if (continuation)
				read_until_complete_rec(command_ref, continuation);
		}
	}
	else
	{
		free(last);
		line_continuation_prompt(KILL, NULL, NULL, NULL);
	}
	free(last);
}

t_status	here_doc_handling(char *last)
{
	// if (last)
	// {
	// 	return (OK);
	// }
	t_status	prompt_status;

	signal(SIGINT, sig_ign);
	prompt_status = here_doc_read(last);
	signal(SIGINT, line_completion_prompt_sig_handler);
	if (prompt_status == ERROR)
		return (ERROR);
	else
		return (OK);
}

static void	send_command_to_parent(char *command,
			int line_channel[2], int line_size_channel[2])
{
	size_t		final_command_len;

	if (command)
	{
		final_command_len = ft_strlen(command);
	}
	else
	{
		final_command_len = 0;
		command = ft_strcpy(NULL, "garbage", sizeof("garbage"));
	}
	write(line_size_channel[1], &final_command_len, sizeof(final_command_len));
	write(line_channel[1], command, final_command_len * sizeof(char));
	free(command);
	close_pipe(line_channel);
	close_pipe(line_size_channel);
}
