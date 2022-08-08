/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:13:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 17:14:06 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

// ! in case of here_doc, len_file_name is len of delimiter
size_t	scan_inout_file(char *command_line, size_t offset, t_token **token_list)
{
	t_token_id		_in_out_;
	size_t			next_word_len; //* file name or here_doc delimiter
	size_t			pre_offset;

	pre_offset = scan_invariants(command_line, offset); // ! ONLY scan_spaces!
	_in_out_ = scan_redir_type(command_line, pre_offset);
	if (_in_out_ == e_NONE)
		return (offset);
	pre_offset += (_in_out_ == e_HERE_DOC || _in_out_ == e_OUT_FILE_APPEND) * 2
		+ (_in_out_ == e_IN_FILE_TRUNC || _in_out_ == e_OUT_FILE_TRUNC);
	pre_offset = scan_invariants(command_line, pre_offset);
	if (!command_line[pre_offset])
		return (offset);
	next_word_len = read_file_name(command_line, pre_offset);
	if (next_word_len == 0)
		return (offset);
	tok_add_back(
		token_list,
		in_out_tok_record_file_name(command_line + pre_offset, next_word_len,
				_in_out_)
	);
	return (pre_offset + next_word_len);
}

size_t	scan_simple_command(char *command_line, size_t offset,
			t_token **token_list)
{
	t_token	*token;
	int		len_cmd_name;
	t_bool	repeat;

//	pre_offset = scan_invariants(command_line, offset);
	// printf(YELLOW "inside scan_simple_command\n" RESET);
	if (!command_line[offset])
		return (offset);
	len_cmd_name = offset;
	// ! DA REFATTORIZZARE! --------------> NAME of function: 
	repeat = e_true;
	while (repeat)
	{
		len_cmd_name = skip_consecutive_chars(command_line, len_cmd_name, '$', +1);
		len_cmd_name += bash_next_word_len(command_line, len_cmd_name);//* was ALONE!!!!!!!!!!!!!!!
		if (command_line[len_cmd_name] != '$')
			repeat = e_false;
	}
	len_cmd_name = len_cmd_name - offset;
	if (len_cmd_name == 0)
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_CMD_NAME;
	token->token_val = ft_strcpy(NULL, command_line + offset, len_cmd_name);
	offset += len_cmd_name;
	offset = scan_redirs(command_line, offset, token_list);
	offset = scan_cmd_arg(command_line, offset, token_list);
	tok_add_back(token_list, token);
	return (offset);
}

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list)
{
	size_t				new_offset;
	t_token				*token;
	t_bindings			*next_var;

	new_offset = scan_initial_keyword_set_token(str, offset, &token);
	new_offset = scan_invariants(str, new_offset);
	while (e_true)
	{
		next_var = NULL;
		new_offset = scan_redirs(str, new_offset, token_list); //scan_inout_file(str, new_offset, token_list);
		new_offset = scan_var(str, new_offset, token->token_id, &next_var);
		if (!next_var)
			break ;
		else if (str[new_offset]
			&& e_false == bash_control_character(str[new_offset]))
			return (scan_env_revert(token, offset));
		else
			env_tok_add_new_binding(&token, next_var);
	}
	if (token->token_id == e_ENV_VAR_DECL && token->token_val == NULL)
		return (scan_env_revert(token, offset));
	env_decl_add_token(token, token_list);
	return (new_offset);
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
	else if (command_line[pre_offset] == '|'
		&& command_line[pre_offset + 1] != '|')
		token->token_val = "|";
	else
		token->token_val = "||";
	tok_add_back(token_list, token);
	return (pre_offset + ft_strlen((char *)token->token_val));
}

size_t	scan_single_par(char *command_line, size_t offset,
			t_token **token_list)
{
	t_token	*token;
	size_t	pre_offset;

	pre_offset = offset;
	pre_offset = scan_spaces(command_line, pre_offset);
	if (command_line[pre_offset] != '(' && command_line[pre_offset] != ')')
		return (offset);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_PARENTHESIS;
	if (command_line[pre_offset] == '(')
		token->token_val = "(";
	else
		token->token_val = ")";
	tok_add_back(token_list, token);
	return (pre_offset + 1);
}
