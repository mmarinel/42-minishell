/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 10:48:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list)
{
	size_t				new_offset;
	t_token				*token;
	t_var_ass_content	*next_var;

	new_offset = scan_export_keyword(str, offset);
	if (new_offset == offset)
		return (offset);
	printf("cursor is:%s\n", str + new_offset);
	token = NULL;
	while (e_true)
	{
		next_var = NULL;
		new_offset = scan_var(str, new_offset, &next_var);
		if (!next_var)
			break ;
		if (!token)
		{
			token = (t_token *) malloc(sizeof(t_token));
			token->token_id =  e_ENV_VAR_DECL;
			token->token_val = NULL;
		}
		next_var->next = (t_var_ass_content *)token->token_val;
		token->token_val =  next_var;
	}
	if (token)
		tok_add_back(token_list, token);
	return (new_offset);
}
