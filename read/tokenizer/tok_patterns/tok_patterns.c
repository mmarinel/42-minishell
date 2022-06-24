/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/24 09:25:41 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

size_t	scan_inout_file(char *command_line, size_t offset, t_token **token_list)
{
	t_token		*token;
	t_token_id	_in_out_;
	size_t		len_file_name;
	size_t		pre_offset;

	pre_offset = scan_invariants(command_line, offset);
	if (command_line[pre_offset] == '<')
		_in_out_ = e_IN_FILE;
	else if (command_line[pre_offset] == '>')
		_in_out_ = e_OUT_FILE;
	else
		return (offset);
	pre_offset = scan_invariants(command_line, pre_offset + 1);
	if (!command_line[pre_offset])
		return (offset);
	len_file_name = mini_next_word_len(command_line, pre_offset);
	if (len_file_name == 0)
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = _in_out_;
	token->token_val
		= ft_strcpy(NULL, command_line + pre_offset, len_file_name);
	tok_add_back(token_list, token);
	return (pre_offset + len_file_name);
}

/**
 * @brief ASF to recognize &&, ||, | only
 * 
 * @param command_line 
 * @return int 
 */
size_t	scan_operator(char *command_line, size_t offset, t_token **token_list)
{
	t_token	*token;
	size_t	pre_offset;

	if (!command_line[offset])
		return (offset);
	pre_offset = scan_invariants(command_line, offset);
	if ((command_line[pre_offset] != '|'
			&& command_line[pre_offset] != '&')
		|| (command_line[pre_offset] == '&'
			&& command_line[pre_offset + 1] != '&'))
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_OPERATOR;
	if (command_line[pre_offset] == '&')
		token->token_val = "&&";
	else if (command_line[pre_offset] == '|' && command_line[pre_offset + 1] != '|')
		token->token_val = "|";
	else
		token->token_val = "||";
	tok_add_back(token_list, token);
	return (pre_offset + ft_strlen((char *)token->token_val));
}

size_t	scan_cmd_name(char *command_line, size_t offset, t_token **token_list)
{
	t_token	*token;
	int		len_cmd_name;
	size_t	pre_offset;

	pre_offset = scan_invariants(command_line, offset);
	if (!command_line[pre_offset])
		return (offset);
	len_cmd_name = mini_next_word_len(command_line, pre_offset);
	if (len_cmd_name == 0)
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_CMD_NAME;
	token->token_val = ft_strcpy(NULL, command_line + pre_offset, len_cmd_name);
	tok_add_back(token_list, token);
	return (pre_offset + len_cmd_name);
}

size_t	scan_cmd_arg(char *command_line, size_t offset, t_token **token_list)
{
	t_token	*token;
	char	*arg;
	int		len_cmd_arg;
	size_t	pre_offset;
	size_t	new_offset;

	pre_offset = scan_invariants(command_line, offset);
	if (!command_line[pre_offset])
		return (offset);
	len_cmd_arg = 0;
	arg = NULL;
	new_offset = pre_offset;
	while (command_line[new_offset])
	{
		new_offset = scan_invariants(command_line, new_offset);
		if (e_true == bash_control_character(command_line[new_offset])
			&& e_false == ft_isspace(command_line[new_offset])
			&& e_false == redirect_char(command_line[new_offset]))
			break ;
		else if (e_true == redirect_char(command_line[new_offset]))
			new_offset = scan_inout_file(command_line, new_offset, token_list);
		else
		{
			len_cmd_arg = mini_next_word_len(command_line, new_offset);
			arg = ft_strjoin(
					arg,
					ft_strjoin(
						ft_strcpy(NULL,command_line + new_offset, len_cmd_arg),
						" ",
						e_true, e_false
					),
					e_true, e_true
				);
			new_offset += len_cmd_arg;
		}
		printf("new_offset: %zu\n", new_offset);
	}
	printf("ciao\n");
	if (arg == NULL)
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_CMD_ARG;
	token->token_val = arg; //ft_strcpy(NULL, command_line + pre_offset, len_cmd_arg);
	tok_add_back(token_list, token);
	return (new_offset); //(pre_offset + len_cmd_arg);
}

	// while (e_false == mini_cmd_separator(command_line[pre_offset + len_cmd_arg])
	// 	&& e_false == redirect_char(command_line[pre_offset + len_cmd_arg])
	// 	&& command_line[pre_offset + len_cmd_arg])
	// 	len_cmd_arg++;

size_t	scan_parenthesis(char *command_line, size_t offset,
			t_token **token_list)
{
	t_token	*token;
	size_t	pre_offset;

	pre_offset = offset;
	pre_offset = scan_spaces(command_line, pre_offset);
	if (command_line[pre_offset] != '(' && command_line[pre_offset] != ')')
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	if (command_line[pre_offset] == '(')
		token->token_val = "(";
	else
		token->token_val = ")";
	tok_add_back(token_list, token);
	return (pre_offset + 1);
}
