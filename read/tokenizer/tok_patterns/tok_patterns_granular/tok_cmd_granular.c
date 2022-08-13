/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cmd_granular.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:06:47 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 16:22:13 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_granular.h"

static size_t	take_next_arg_len(char *command_line, size_t offset);
//* end of static declarations

size_t	scan_cmd_arg(char *command_line, size_t offset, t_token **token_list)
{
	t_token	*token;
	char	*args;
	size_t	pre_offset;
	size_t	new_offset;

	new_offset = scan_invariants(command_line, offset);
	if (!command_line[new_offset])
		return (offset);
	args = NULL;
	while (command_line[new_offset])
	{
		new_offset = scan_invariants(command_line, new_offset);
		pre_offset = new_offset;
		new_offset = scan_next_cmd_arg(command_line, new_offset,
				&args, token_list);
		if (pre_offset == new_offset)
			break ;
	}
	if (args == NULL)
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	// printf(YELLOW "malloc in tok_cmd_granular.c line 41: %p\n" RESET, token);
	// fflush(stdout);
	token->token_id = e_CMD_ARG;
	token->token_val = args;
	tok_add_back(token_list, token);
	return (new_offset);
}

size_t	scan_next_cmd_arg(char *command_line, size_t offset,
			char **cur_arg_string, t_token **token_list)
{
	size_t	new_offset;
	size_t	len_cmd_arg;
	char	*next_arg;

	new_offset = scan_invariants(command_line, offset);
	if (e_true == redirect_char(command_line[new_offset]))
	{
		new_offset = scan_inout_file(command_line, new_offset, token_list);
	}
	else
	{
		len_cmd_arg = take_next_arg_len(command_line, new_offset);
		next_arg = ft_strcpy(NULL, command_line + new_offset, len_cmd_arg);
		if (!(*cur_arg_string))
			*cur_arg_string = next_arg;
		else
			(*cur_arg_string) = ft_strjoin(
					(*cur_arg_string),
					ft_strjoin(" ", next_arg, e_false, e_true),
					e_true, e_true);
		new_offset += len_cmd_arg;
	}
	return (new_offset);
}

static size_t	take_next_arg_len(char *command_line, size_t offset)
{
	return (bash_next_string_len(command_line, offset));
}
