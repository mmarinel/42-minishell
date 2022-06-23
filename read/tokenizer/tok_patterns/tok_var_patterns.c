/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 17:49:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

static void	add_new_binding(t_token **token_ref,
				t_var_ass_content *next_binding);

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list)
{
	size_t				new_offset;
	t_token				*token;
	t_var_ass_content	*next_var;

	new_offset = scan_export_keyword(str, offset);
	if (new_offset == offset)
		return (offset);
	token = NULL;
	while (e_true)
	{
		next_var = NULL;
		new_offset = scan_inout_file(str, new_offset, token_list);
		printf("after export infile: %s\n", str + new_offset);
		new_offset = scan_var(str, new_offset, &next_var);
		if (!next_var)
			break ;
		else
			add_new_binding(&token, next_var);
	}
	if (token)
		tok_add_back(token_list, token);
	return (new_offset);
}

static void	add_new_binding(t_token **token_ref,
		t_var_ass_content *next_binding)
{
	if (!(*token_ref))
	{
		(*token_ref) = (t_token *) malloc(sizeof(t_token));
		(*token_ref)->token_id = e_ENV_VAR_DECL;
		(*token_ref)->token_val = NULL;
	}
	next_binding->next = (t_var_ass_content *)(*token_ref)->token_val;
	(*token_ref)->token_val = next_binding;
}
