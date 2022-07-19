/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_in_out_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:07:49 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/19 11:09:44 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_utils.h"

static size_t	take_here_docs(void);

//* end of static declarations


t_token_id	scan_redir_type(char *command_line, size_t offset)
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

t_token	*in_out_tok_record_file_name(char *next_word_begin, size_t next_word_len,
			t_token_id _in_out_)
{
	t_token		*token;
	static int	cur_hdoc_cont_id = -1;
	size_t		here_docs;

	here_doc_init:
	{
		here_docs = take_here_docs();
		if (cur_hdoc_cont_id == -1)
			cur_hdoc_cont_id = here_docs - 1;
	}
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = _in_out_;
	if (_in_out_ != e_HERE_DOC)
		token->token_val
			= ft_strcpy(NULL, next_word_begin, next_word_len);
	else
	{
		token->token_val = ft_strjoin(
			".here_doc-",
			ft_itoa((here_docs - cur_hdoc_cont_id) - 1),//ft_itoa(*here_docs),
			e_false, e_true);
		printf("cur here_doc name: %s\n", token->token_val);
		cur_hdoc_cont_id--;
	}
	return (token);
}

size_t	read_file_name(char *str, size_t offset)
{
	size_t	len_file_name;
	size_t	prefix_len;

	if (str[offset] == '&' && str[offset + 1] != '&')
	{
		offset += 1;
		prefix_len = 1;
	}
	else
	{
		prefix_len = 0;
	}
	len_file_name = prefix_len + bash_next_word_len(str, offset);
	return (len_file_name);
}

static size_t	take_here_docs(void)
{
	size_t	i;
	char	*hdoc_file_name;
	char	*prefix;
	t_bool	repeat;

	prefix = ".here_doc-";
	i = 0;
	repeat = e_true;
	while (repeat)
	{
		hdoc_file_name = ft_strjoin(
			prefix, ft_itoa(i),
			e_false, e_true
		);
		if (0 != access(hdoc_file_name, R_OK | W_OK))
			repeat = e_false;
		else
			i++;
		free(hdoc_file_name);
		// i++;
	}
	printf("%zu here-docs detected\n", i); 
	return (i);
}
