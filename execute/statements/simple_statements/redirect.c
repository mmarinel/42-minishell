/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:13:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 21:56:27 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

static void		external_close_pipe(int cur_in_out);
static t_status	external_redir_in_or_out(t_redirection redir,
					int *cur_in_out,
					t_bool input_redir_case);
//* end of static declarations

/**
 * @brief this function handles redirections for non builtin commands.
 * 
 * @param redir 
 * @param cur_in_out 
 * @param std_in_out 
 * @param input_redir_case 
 */
t_status	external_handle_redirs(t_redirection redir, int cur_in_out,
				int std_in_out, t_bool input_redir_case)
{
	t_status	outcome;

	outcome = OK;
	if (redir.file_name)
	{
		if (cur_in_out != std_in_out)
		{
			external_close_pipe(cur_in_out);
		}
		outcome = external_redir_in_or_out(redir, &cur_in_out,
				input_redir_case);
	}
	if (outcome == OK)
		dup_std_fd(cur_in_out, std_in_out, e_true);
	return (outcome);
}

static t_status	external_redir_in_or_out(t_redirection redir, int *cur_in_out,
				t_bool input_redir_case)
{
	{
		if (input_redir_case == e_true)
		{
			*cur_in_out = open(redir.file_name, O_RDONLY);
		}
		else
		{
			if (redir.append_mode == e_true)
				*cur_in_out = ft_open(redir.file_name,
						O_CREAT | O_APPEND | O_WRONLY, 0777, e_false);
			else
				*cur_in_out = ft_open(redir.file_name,
						O_CREAT | O_TRUNC | O_WRONLY, 0777, e_false);
		}
	}
	{
		if (-1 == *cur_in_out)
			return (ERROR);
		else
			return (OK);
	}
}

static void	external_close_pipe(int cur_in_out)
{
	close(cur_in_out);
}

/**
 * @brief This function handles redirections for builtin commands.
 * N.B.: if inside a pipe without an explicit redirection, we do not close
 * the pipe because we are not an independent process!.
 * 
 * @param redir 
 * @param cur_in_out 
 * @param std_in_out 
 * @param input_redir_case 
 */
t_status	builtin_handle_redirs(t_redirection redir, int cur_in_out,
				int std_in_out, t_bool input_redir_case)
{
	if (redir.file_name)
	{
		if (input_redir_case == e_true)
		{
			cur_in_out = open(redir.file_name, O_RDONLY);
		}
		else
		{
			if (redir.append_mode == e_true)
				cur_in_out = ft_open(redir.file_name,
						O_CREAT | O_APPEND | O_WRONLY, 0777, e_false);
			else
				cur_in_out = ft_open(redir.file_name,
						O_CREAT | O_TRUNC | O_WRONLY, 0777, e_false);
		}
		dup_std_fd(cur_in_out, std_in_out, e_true);
		if (-1 == cur_in_out)
			return (ERROR);
	}
	else
	{
		dup_std_fd(cur_in_out, std_in_out, e_false);
	}
	return (OK);
}

t_status	open_paren_node_redirs(int *in, int *out,
				t_node_content *parenthesis_node)
{
	if (parenthesis_node->in_redir.file_name)
	{
		*in = open(parenthesis_node->in_redir.file_name, O_RDONLY);
		if (*in == -1)
			return (ERROR);
	}
	if (parenthesis_node->out_redir.file_name)
	{
		if (parenthesis_node->out_redir.append_mode == e_true)
			*out = ft_open(parenthesis_node->out_redir.file_name,
					O_CREAT | O_APPEND | O_WRONLY, 0777, e_false);
		else
			*out = ft_open(parenthesis_node->out_redir.file_name,
					O_CREAT | O_TRUNC | O_WRONLY, 0777, e_false);
		if (*out == -1)
			return (ERROR);
	}
	return (OK);
}
