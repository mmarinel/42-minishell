/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var_patterns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:47:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/27 16:06:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

static size_t	scan_env_revert(t_token *token, size_t offset);

static void	add_new_binding(t_token **token_ref,
				t_bindings *next_binding);

static void	env_decl_add_token(t_token *scanned_token, t_token **token_list);

static size_t	scan_initial_keyword_set_token(char *str, size_t offset, t_token **token);

// * End of declarations *//

size_t	scan_env_declaration(char *str, size_t offset, t_token **token_list)
{
	size_t				new_offset;
	t_token				*token;
	t_bindings			*next_var;

	new_offset = scan_initial_keyword_set_token(str, offset, &token);
	if (new_offset == offset)
		return (offset);
	new_offset = scan_invariants(str, new_offset);
	while (e_true)
	{
		next_var = NULL;
		new_offset = scan_redirs(str, new_offset, token_list); //scan_inout_file(str, new_offset, token_list);
		new_offset = scan_var(str, new_offset, token->token_id, &next_var);
		if (!next_var)
			break ;
		else if (token->token_id == e_ENV_VAR_UNSET
			&& str[new_offset]
			&& e_false == bash_control_character(str[new_offset]))
			return (scan_env_revert(token, offset));
		else
			add_new_binding(&token, next_var);
	}
	env_decl_add_token(token, token_list);
	return (new_offset);
}

static size_t	scan_env_revert(t_token *token, size_t offset)
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

static size_t	scan_initial_keyword_set_token(char *str, size_t offset, t_token **token)
{
	size_t	new_offset;

	new_offset = scan_invariants(str, offset);
	if (str[new_offset] == '\0'
		||
		(ft_strncmp(str + new_offset, "export", 6) != 0
			&& ft_strncmp(str + new_offset, "unset", 5) != 0))
		return (offset);
	else
	{
		(*token) = (t_token *) malloc(sizeof(t_token));
		(*token)->token_val = NULL;
		(*token)->to_string = NULL;
		(*token)->next = NULL;
		// (*token)->prev = NULL;
		if (ft_strncmp(str + new_offset, "export", 6) == 0)
		{
			(*token)->token_id =  e_ENV_VAR_DECL;
			return (new_offset + 6);
		}
		if (ft_strncmp(str + new_offset, "unset", 5) == 0)
		{
			(*token)->token_id =  e_ENV_VAR_UNSET;
			return (new_offset + 5);
		}
	}
	return (0);
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
		t_bindings *next_binding)
{
	next_binding->next = (t_bindings *)(*token_ref)->token_val;
	(*token_ref)->token_val = next_binding;
}

static void	env_decl_add_token(t_token *scanned_token, t_token **token_list)
{
	tok_add_back(token_list, scanned_token);
}
