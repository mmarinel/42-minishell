/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 08:57:20 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

int	scan_var(char *str)
{
	int					new_offset;
	char				*cursor;
	t_var_ass_content	*next_var;
	t_token				*token;

	new_offset = scan_spaces(str) + scan_invariant_quotes(str);
	if (str[new_offset] == '\0'
		|| ft_strncmp(str + new_offset, "export", 6 * sizeof(char)) != 0)
		return (0);
	new_offset += 6;
	cursor = str + new_offset;
	token = NULL;
	while (e_true)
	{
		next_var = scan_var_set_cursor(cursor, &cursor, token == NULL);
		if (!next_var)
			break ;
		if (!token)
		{
			token = (t_token *) malloc(sizeof(t_token));
			token->token_id =  e_ENV_VAR_ASSIGN;
		}
		next_var->next = token->token_val;
		token->token_val =  next_var;
	}
	new_offset = ft_strlen(str) - ft_strlen(cursor); // + 1;
	if (token)
		lexer(token, e_STORE_NXT_TOK);
	return (new_offset);
}
