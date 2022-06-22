/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 12:53:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

int	scan_var(char *str, t_token **token_list)
{
	int					new_offset;
	char				*cursor;
	t_var_ass_content	*next_var;
	t_token				*token;

	new_offset = scan_spaces(str);
	new_offset += scan_invariant_quotes(str);
	if (0 == scan_export_keyword(str + new_offset))
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
		tok_add_back(token_list, token);
	return (new_offset);
}

int	scan_export_keyword(char *cursor)
{
	if (*cursor == '\0'
		|| ft_strncmp(cursor, "export", 6 * sizeof(char)) != 0)
		return (0);
	return (6);
}
