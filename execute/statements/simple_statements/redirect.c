/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:13:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 16:25:57 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

static void	ft_dup(int cur_in_out, int std_in_out, t_bool close_cur);

//* end of static declarations

/**
 * @brief this function handles redirections for non builtin commands.
 * 
 * @param redir 
 * @param cur_in_out 
 * @param std_in_out 
 * @param input_redir_case 
 */
void	external_handle_redirs(t_redirection redir, int cur_in_out,
			int	std_in_out, t_bool input_redir_case)
{
	if (redir.file_name)
	{
		if (cur_in_out != std_in_out)
		close_pipe:
		{
			close(cur_in_out);
		}
		redir_in_or_out:
		{
			if (input_redir_case == e_true)
				cur_in_out = open(redir.file_name, O_RDONLY);
			else
			{
				if (redir.append_mode == e_true)
					cur_in_out = ft_open(redir.file_name,
								O_CREAT | O_APPEND | O_WRONLY, 0777, e_false);
				else
					cur_in_out = ft_open(redir.file_name,
								O_CREAT | O_TRUNC | O_WRONLY, 0777, e_false);
			}
		}
	}
	ft_dup(cur_in_out, std_in_out, e_true);
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
void	builtin_handle_redirs(t_redirection redir, int cur_in_out,
			int	std_in_out, t_bool input_redir_case)
{
	if (redir.file_name)
	{
		if (input_redir_case == e_true)
			cur_in_out = open(redir.file_name, O_RDONLY);
		else
		{
			if (redir.append_mode == e_true)
				cur_in_out = ft_open(redir.file_name,
							O_CREAT | O_APPEND | O_WRONLY, 0777, e_false);
			else
				cur_in_out = ft_open(redir.file_name,
							O_CREAT | O_TRUNC | O_WRONLY, 0777, e_false);
		}
		ft_dup(cur_in_out, std_in_out, e_true);
	}
	else
	{
		ft_dup(cur_in_out, std_in_out, e_false);
	}
}

static void	ft_dup(int cur_in_out, int std_in_out, t_bool close_cur)
{
	if (cur_in_out != std_in_out)
	{
		dup2(cur_in_out, std_in_out);
		if (close_cur == e_true)
			close(cur_in_out);
	}
}
