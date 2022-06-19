/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:48:51 by earendil          #+#    #+#             */
/*   Updated: 2022/06/19 11:25:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// ! to DECOMMENT !!!!!!!!!!!!!!!!!!!!!!!!!!
int	scan_name(char **str, t_op_code	*possible_names);


// ! to DECOMMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static void	*lexer(void *arg, t_op_code op_code)
{
	static char		*__input_string = NULL;
	static int		offset = -1;
	static t_token	*cur_token = NULL;

	if (op_code == e_CLEAN)
	{
		ft_free(__input_string);
		__input_string = NULL;
		ft_free(cur_token);
		cur_token = NULL;
		offset = -1;
	}
	if (op_code == e_STORE_STR || op_code == e_RETURN_CUR_STR
		|| op_code == e_ADVANCE_STR)
		return (lexer_input_handling(arg,
				&__input_string, &offset, op_code));
	else if (op_code == e_STORE_NXT_TOK || op_code == e_RETURN_TOK)
		return (lexer_token_handling(arg,
				&cur_token, op_code));
	return (NULL);
}

void	tokenizer_feed_input(char **input_str_ref)
{
	if (input_str_ref == NULL)
		return ;
	lexer(input_str_ref, e_STORE_STR);
}

t_token	*get_cur_token(void)
{
	return (lexer(NULL, e_RETURN_TOK));
}
*/

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
