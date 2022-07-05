/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_continuation_prompt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 16:32:56 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_continuation_prompt.h"

static void	read_until_complete(char **continuation,
			int line_channel[2], int line_size_channel[2]);
static char	*read_until_complete_rec(char **old);

// * end of static declarations //


void	line_continuation_prompt(t_prompt_behav opcode,
			int line_channel[2], int line_size_channel[2])
{
	static char	*continuation = NULL;

	if (opcode == KILL)
	{
		ft_free(continuation);
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
	size_t	continuation_len;

	read_until_complete_rec(continuation);
	if (*continuation)
	{
		continuation_len = ft_strlen(*continuation);
	}
	else
	{
		continuation_len = 1;
		*continuation = ft_strcpy(NULL, "", 0);
	}
	write(line_size_channel[1], &continuation_len, sizeof(continuation_len));
	write(line_channel[1], *continuation, continuation_len * sizeof(char));
	free(*continuation);
	close_pipe(line_channel);
	close_pipe(line_size_channel);
}

static char	*read_until_complete_rec(char **old)
{
	char	*continuation;

	continuation = readline("> ");
	if (!continuation)
		return (*old);
	else if (*continuation == '\0')
		return (read_until_complete_rec(old));
	else
	{
		*old = ft_strjoin(*old, continuation, e_true, e_true);
		{
			if (e_true == ft_pending_pipe(*old)
				|| e_true == ft_pending_logical_op(*old))
				return (read_until_complete_rec(old));
			else
				return (*old);
		}
	}
}
