/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 09:46:49 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_utils.h"

size_t	scan_env_revert(t_token *token, size_t offset)
{
	t_bindings	*cur;
	t_bindings	*prev;

	cur = (t_bindings *) token->token_val;
	while (cur)
	{
		prev = cur;
		cur =  cur->next;
		free(prev);
	}
	free(token);
	return (offset);
}

size_t	scan_initial_keyword_set_token(char *str, size_t offset, t_token **token)
{
//	new_offset = scan_invariants(str, offset);
	if (str[offset] == '\0'
		||
		(ft_strncmp(str + offset, "export", 6) != 0
			&& ft_strncmp(str + offset, "unset", 5) != 0))
		return (offset);
	else
	{
		(*token) = (t_token *) malloc(sizeof(t_token));
		(*token)->token_val = NULL;
		(*token)->to_string = NULL;
		(*token)->next = NULL;
		// (*token)->prev = NULL;
		if (ft_strncmp(str + offset, "export", 6) == 0)
		{
			(*token)->token_id =  e_ENV_VAR_DECL;
			return (offset + 6);
		}
		if (ft_strncmp(str + offset, "unset", 5) == 0)
		{
			(*token)->token_id =  e_ENV_VAR_UNSET;
			return (offset + 5);
		}
	}
	return (0);
}

void	add_new_binding(t_token **token_ref,
		t_bindings *next_binding)
{
	next_binding->next = (t_bindings *)(*token_ref)->token_val;
	(*token_ref)->token_val = next_binding;
}

void	env_decl_add_token(t_token *scanned_token, t_token **token_list)
{
	tok_add_back(token_list, scanned_token);
}
