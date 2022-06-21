/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:48:51 by earendil          #+#    #+#             */
/*   Updated: 2022/06/21 13:26:54 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// ! to DECOMMENT !!!!!!!!!!!!!!!!!!!!!!!!!!
int	scan_name(char **str, t_op_code	*possible_names);

void	tokenizer_feed_input(char **input_str_ref)
{
	if (input_str_ref == NULL)
		return ;
	lexer(NULL, e_CLEAN);
	lexer(input_str_ref, e_STORE_STR);
}

t_token	*get_cur_token(void)
{
	return (lexer(NULL, e_RETURN_TOK));
}


void	tokenize(char	*str)
{
	size_t	offset;

	offset = 0;
	while (*str)
	{
		str += scan_in_out_file_toks(str);
		str += scan_command(str); // TODO:-> contains str += scan_cmd_continuation(str); while loop scanning in_out files and then cmd arg until there are no more cmd_args
								// TODO: scan_command checks variable assignments (i.e.: while loop scanning variable and then in_out file) then scans cmd name, then in_out file and then cmd args (uP)
		str += scan_in_out_file_toks(str);
		str += scan_operator(str);

	}
}

// ! TO DECOMMENT !!!!!!!!!!!!!!!!!
void	scan_next_token(void)
{
	char	*cur_str;
	int		new_offset;

	new_offset = -1;
	cur_str = (char *)lexer(NULL, e_RETURN_CUR_STR);
	if (cur_str[0] == '&' || cur_str[0] == '|'
		|| cur_str[0] == '='
		|| cur_str[0] == '>' || cur_str[0] == '<')
		new_offset = scan(&cur_str, e_OPERATOR);
	else if (cur_str[0] == '"')
		new_offset = scan(&cur_str, e_DOUBLE_QUOTE);
	else if (cur_str[0] == '\'')
		new_offset = scan(&cur_str, e_SINGLE_QUOTE);
	else if (cur_str[0] == '-')
		new_offset = scan(&cur_str, e_ARG);
	else if (cur_str[0] == e_EXPORT)
		new_offset = scan(&cur_str, e_EXPORT);
	else
		new_offset = scan_name(&cur_str,
				(t_op_code *){e_VAR_NAME, e_USR_PROGRAM, e_FILENAME, e_NONE});
	if (new_offset == -1)
		lexer(NULL, e_CLEAN);
	else
		lexer(new_offset, e_ADVANCE_STR);
}

void	scan_next_token(void)
{
	char	*cur_str;
	int		new_offset;

	new_offset = -1;
	cur_str = (char *)lexer(NULL, e_RETURN_CUR_STR);
	if (cur_str[0] == '-')
		new_offset = scan(&cur_str, e_ARG);
	else if (cur_str[0] == '&&' || cur_str[0] == '||'
		|| cur_str[0] == '='
		|| cur_str[0] == '|'
		|| cur_str[0] == '>' || cur_str[0] == '<' || cur_str[0] == '>>'
		|| cur_str[0] == '<<')
		new_offset = scan(&cur_str, e_OPERATOR);
	else if (cur_str[0] == '"' || cur_str[0] == '\'')
		new_offset = scan(&cur_str, e_STRING_LITERAL);
	else
		new_offset = scan(&cur_str, e_IDENTIFIER);
	if (new_offset == -1)
		lexer(NULL, e_CLEAN);
}

int	scan(char **str, t_token_id tok_id)
{
	char	*cur;

	while (*cur)
	{
		if (ft_isspace(*cur) == e_false
			|| dels_member(*cur, (int []){'-',
				'&&', '||', '=', '|', '>>', '>', '<', '<<', '"', '\''}))
			;
	}
}
