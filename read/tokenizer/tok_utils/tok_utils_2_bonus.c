/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:36:08 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/20 14:43:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

t_token	*scan_var_set_cursor(char *str, char **cursor, t_token_id var_type)
{
	char	*var_name;
	char	*var_value;
	t_token	*token;

	var_name = NULL;
	var_value = NULL;
	(*cursor) = scan_var_name(str, &var_name);
	if (!(*cursor)
		|| (var_type == e_SHELL_VAR_NAME && *(*cursor) != "="))
	{
		ft_free(var_name);
		return (NULL);
	}
	(*cursor) = scan_var_value((*cursor), &var_value);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_NONE;
	token->token_val = (t_var_content *) malloc(sizeof(t_var_content));
	((t_var_content *)(token->token_val))->name = var_name;
	((t_var_content *)(token->token_val))->val = var_value;
	/*	= string_strip(
			string_strip(var_value, '"', e_true),
			'\'', e_true); */
	return (token);
}

int	scan_var(char *str, t_token_id var_type)
{
	char	*cursor;
	int		new_offset;
	t_token	*token;

	if (!str || !(*str))
		return (-1);
	cursor = str;
	token = scan_var_set_cursor(str, &cursor, var_type);
	if (!token)
		return (-1);
	token->token_id = var_type;
	new_offset = ft_strlen(str) - ft_strlen(cursor); // + 1;
	lexer(token, e_STORE_NXT_TOK);
	return (new_offset);
}

int	scan_alternate_invariant_spaces_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		// READING ALL INVARIANT QUOTES
		while (str[idx] == '"' || str[idx] == '\'')
		{
			if (str[idx + 1] != str[idx])
				break ;
			idx += 2;
		}
		// READING ALL FINAL SPACES
		while (str[idx])
		{
			if (e_false == ft_isspace(str[idx]))
				break ;
			idx++;
		}
		if (str[idx] != '"' && str[idx] != '\''
			&& e_false == ft_isspace(str[idx]))
			break ;
	}
	return (idx);
}

int	scan_spaces(char *str)
{
	int	idx;

	idx = 0;
	while (e_true == ft_isspace(str[idx]))
		idx++;
	return (idx);
}

int	scan_invariant_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] == '"' || str[idx] == '\'')
	{
		if (str[idx + 1] != str[idx])
			break ;
		idx += 2;
	}
	return (idx);
}
