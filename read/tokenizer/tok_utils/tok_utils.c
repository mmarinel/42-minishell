/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 09:35:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

static void	free_tok_list_rec(t_token *token);
static void	tok_to_string(t_token *token);

// int	scan_alternate_invariant_spaces_quotes(char *str)
// {
// 	int	idx;

// 	idx = 0;
// 	while (str[idx])
// 	{
// 		// READING ALL INVARIANT QUOTES
// 		while (str[idx] == '"' || str[idx] == '\'')
// 		{
// 			if (str[idx + 1] != str[idx])
// 				break ;
// 			idx += 2;
// 		}
// 		// READING ALL FINAL SPACES
// 		while (str[idx])
// 		{
// 			if (e_false == ft_isspace(str[idx]))
// 				break ;
// 			idx++;
// 		}
// 		if (str[idx] != '"' && str[idx] != '\''
// 			&& e_false == ft_isspace(str[idx]))
// 			break ;
// 	}
// 	return (idx);
// }

/**
 * @brief this function adds the given token to the end of the current list of tokens (circular list only on prev pointers)
 * 
 * @param token_list the address of the first element in the list
 * @param token the next token to store or NULL to close the list
 */
void	tok_add_back(t_token **token_list, t_token *token)
{
	static	t_token	*tail = NULL;

	if (!token && *token_list)
		(*token_list)->prev = tail;
	else
	{
		if (!(*token_list))
		{
			*token_list = token;
			tail = *token_list;
			tail->prev = NULL;
			tail->next = NULL;
		}
		else
		{
			tail->next = token;
			tail->next->prev = tail;
			tail = tail->next;
			tail->next = NULL;
		}
		token->to_string = tok_to_string;
	}
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
	free(token);
}

static void	tok_to_string(t_token *token)
{
	char	*id;

	id = "NONE";
	if (token->token_id == e_NONE)
		id = "NONE";
	if (token->token_id == e_CMD_NAME)
		id = "CMD_NAME";
	if (token->token_id == e_CMD_ARG)
		id = "CMD_ARG";
	if (token->token_id == e_IN_FILE)
		id = "IN_FILE";
	if (token->token_id == e_OUT_FILE)
		id = "OUT_FILE";
	if (token->token_id == e_OUT_FILE)
		id = "OUT_FILE";
	if (token->token_id == e_OPERATOR)
		id = "OPERATOR";
	if (token->token_id == e_ENV_VAR_DECL)
		id = "ENV_VAR_ASSIGNATION";
	if (token->token_id == e_PARENTHESIS)
		id = "PARENTHESIS";
	printf("%s ", id);
}
