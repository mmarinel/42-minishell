/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_in_out_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:07:49 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 10:00:07 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_utils.h"

t_token_id	scan_in_out_init(char *command_line, size_t offset)
{
	t_token_id	_in_out_;

	_in_out_ = e_NONE;
	if (command_line[offset] == '<' && command_line[offset + 1] == '<')
		_in_out_ = e_HERE_DOC;
	else if (command_line[offset] == '<')
		_in_out_ = e_IN_FILE_TRUNC;
	else if (command_line[offset] == '>' && command_line[offset + 1] == '>')
		_in_out_ = e_OUT_FILE_APPEND;
	else if (command_line[offset] == '>')
		_in_out_ = e_OUT_FILE_TRUNC;
	return (_in_out_);
}

t_token	*scan_in_out_finalize(char *next_word_begin, size_t next_word_len,
			t_token_id _in_out_, size_t *here_docs)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = _in_out_;
	if (_in_out_ != e_HERE_DOC)
		token->token_val
			= ft_strcpy(NULL, next_word_begin, next_word_len);
	else
	{
		token->token_val = ft_strjoin(".here_doc-", ft_itoa(*here_docs),
								e_false, e_true);
		*here_docs += 1;
	}
	return (token);
}

size_t	read_file_name(char *str, size_t offset)
{
	size_t	len_file_name;

	if (str[offset] == '&' && str[offset + 1] != '&')
	{
		offset += 1;
		len_file_name = 1;
	}
	else
		len_file_name = 0;
	len_file_name += bash_next_word_len(str, offset);
	return (len_file_name);
}
