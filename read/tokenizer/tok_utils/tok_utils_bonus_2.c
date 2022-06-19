/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_bonus_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:36:08 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 20:57:28 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

t_token	*scan_var_set_cursor(char *str, char **cursor)
{
	char	*var_name;
	char	*var_value;
	t_token	*token;

	var_name = NULL;
	var_value = NULL;
	(*cursor) = scan_var_name(str, &var_name);
	if (!(*cursor))
		return (NULL);
	if (*(*cursor) == "=")
		(*cursor) = scan_var_value((*cursor), &var_value);
	token = (t_token *) malloc(sizeof(t_token));
	token->token_id = e_NONE;
	token->token_val = (t_var_content *) malloc(sizeof(t_var_content));
	((t_var_content *)(token->token_val))->name = var_name;
	((t_var_content *)(token->token_val))->val = var_value;
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
	token = scan_var_set_cursor(str, &cursor);
	if (!token)
		return (-1);
	token->token_id = var_type;
	new_offset = ft_strlen(str) - ft_strlen(cursor); // + 1;
	lexer(token, e_STORE_NXT_TOK);
	return (new_offset);
}
