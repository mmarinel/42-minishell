/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_memory_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:23:11 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/14 11:47:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

static void	free_tok_list_rec(t_token *token);
static void	free_tok_val(t_token *token);
// * end of declarations //

/**
 * @brief this function adds the given token
 * to the end of the current list of tokens
 * 
 * @param tokens the address of the first element
 * in the list (optional if the list is not empty)
 * @param token the next token to store
 */
void	tok_add_back(t_token **token_list, t_token *token)
{
	static t_token	*tail = NULL;

	if (!(*token_list))
	{
		*token_list = token;
		tail = *token_list;
	}
	else
	{
		tail->next = token;
		tail = tail->next;
	}
	tail->next = NULL;
}

void	free_tok_list(t_token **token_list)
{
	if (*token_list)
	{
		free_tok_list_rec(*token_list);
		*token_list = NULL;
	}
}

static void	free_tok_list_rec(t_token *token)
{
	if (token->next)
		free_tok_list_rec(token->next);
	free_tok_val(token);
	free(token);
}

static void	free_tok_val(t_token *token)
{
	if (token->token_id == e_CMD_NAME
		|| token->token_id == e_CMD_ARG
		|| token->token_id == e_OUT_FILE_APPEND
		|| token->token_id == e_OUT_FILE_TRUNC
		|| token->token_id == e_IN_FILE_TRUNC
		|| token->token_id == e_HERE_DOC)
		free(token->token_val);
	if (token->token_id == e_ENV_VAR_DECL
		|| token->token_id == e_ENV_VAR_UNSET)
		free_env(token->token_val);
}
