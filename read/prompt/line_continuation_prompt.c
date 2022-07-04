/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_continuation_prompt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:41:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 19:33:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char		*append_continuation(char *command,
					int line_channel[], int line_size_channel[]);
static void		line_completion_prompt(int line_channel[],
					int line_size_channel[]);
static char		*final_line(char *command, int cont_prompt_return,
					int line_size_channel[], int line_channel[]);

// TODO :-> return EXIT CODE 258 for ctrl + D while 
// TODO trying to complete line (exit/errors module)
char	*prompt_complete_line(char *command)
{
	int		line_size_channel[2];
	int		line_channel[2];
	pid_t	cont_prompt_pid;
	int		cont_prompt_return;

	pipe(line_size_channel);
	pipe(line_channel);
	while (e_false == ft_quote_occurrence_balanced(command))
	{
		cont_prompt_pid = fork();
		if (!cont_prompt_pid)
			line_completion_prompt(line_channel, line_size_channel);
		else
		{
			waitpid(cont_prompt_pid, &cont_prompt_return, 0);
			if (cont_prompt_return != EXIT_SUCCESS)
				break ;
			command = append_continuation(command,
					line_channel, line_size_channel);
		}
	}
	return (
		final_line(command, cont_prompt_return,
			line_size_channel, line_channel)
	);
}

static char	*append_continuation(char *command,
		int line_channel[], int line_size_channel[])
{
	char	*continuation;
	int		cont_len;

	read(line_size_channel[0], &cont_len, sizeof(cont_len));
	continuation = (char *) malloc((cont_len + 1) * sizeof(char));
	read(line_channel[0], continuation, (cont_len + 1) * sizeof(char));
	continuation[cont_len] = '\0';
	return (ft_strjoin(command, continuation, e_true, e_true));
}

// TODO :-> return EXIT CODE 258 for ctrl + D while 
// TODO trying to complete line (exit/errors module)
static void	line_completion_prompt(int line_channel[], int line_size_channel[])
{
	char	*continuation;
	int		cont_len;

	signal(SIGINT, line_completion_prompt_sig_handler);
	while (e_true)
	{
		continuation = readline(">");
		if (!continuation)
			exit_shell(EXIT_FAILURE, e_false);
		if (*continuation == '\0')
			free(continuation);
		else
			break ;
	}
	cont_len = (int) ft_strlen(continuation);
	write(line_channel[1], continuation, cont_len * sizeof(char));
	write(line_size_channel[1], &cont_len, sizeof(cont_len));
	exit(EXIT_SUCCESS);
}

static char	*final_line(char *command, int cont_prompt_return,
		int line_size_channel[], int line_channel[])
{
	close_pipe(line_size_channel);
	close_pipe(line_channel);
	if (cont_prompt_return != EXIT_SUCCESS)
	{
		free(command);
		return (NULL);
	}
	return (command);
}
