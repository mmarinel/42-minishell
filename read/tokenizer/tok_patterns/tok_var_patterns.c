/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/24 13:14:04 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

static void	add_new_binding(t_token **token_ref,
				t_var_ass_content *next_binding);

static void	env_decl_add_token(t_token *scanned_token, t_token **token_list);

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list)
{
	size_t				new_offset;
	t_token				*token;
	t_var_ass_content	*next_var;

	new_offset = scan_export_keyword(str, offset);
	if (new_offset == offset)
		return (offset);
	new_offset = scan_invariants(str, new_offset);
	token = NULL;
	while (e_true)
	{
		next_var = NULL;
		new_offset = scan_inout_file(str, new_offset, token_list);
		new_offset = scan_var(str, new_offset, &next_var);
		if (!next_var)
			break ;
		else
			add_new_binding(&token, next_var);
	}
	env_decl_add_token(token, token_list);
	return (new_offset);
}


	// if (str[new_offset] != '\0'
	// 	&& e_false == mini_cmd_separator(str[new_offset]))
	// {
	// 	free(token);
	// 	return (offset);
	// }
	// else if (token)
	// 	tok_add_back(token_list, token);
	// return (new_offset);

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

static void	env_decl_add_token(t_token *scanned_token, t_token **token_list)
{
	t_token	*export_keyword_only;

	if (!scanned_token)
	{
		export_keyword_only = (t_token *) malloc(sizeof(t_token));
		export_keyword_only->token_id = e_ENV_VAR_DECL;
		export_keyword_only->token_val = NULL;
		export_keyword_only->to_string = NULL;
		export_keyword_only->next = NULL;
		export_keyword_only->prev = NULL;
		tok_add_back(token_list, export_keyword_only);
	}
	else
		tok_add_back(token_list, scanned_token);
}
