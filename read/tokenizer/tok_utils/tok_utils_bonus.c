/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 10:48:11 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

static void	free_tok_list_rec(t_token *token);

int	scan_alternate_invariant_spaces_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		// READING ALL INVARIANT QUOTES
		while (str[idx] == '"' || str[idx] == '\'')
		{
			if (str[idx + 1] != str[idx])
				break ;
			idx += 2;
		}
		// READING ALL FINAL SPACES
		while (str[idx])
		{
			if (e_false == ft_isspace(str[idx]))
				break ;
			idx++;
		}
		if (str[idx] != '"' && str[idx] != '\''
			&& e_false == ft_isspace(str[idx]))
			break ;
	}
	return (idx);
}

/**
 * @brief this function adds the given token to the end of the current list of tokens
 * 
 * @param tokens the address of the first element in the list or NULL if the list is not empty
 * @param token the next token to store or NULL to close the list
 */
void	tok_add_back(t_token **tokens, t_token *token)
{
	static	t_token	*tail;

	if (tokens)
	{
		*tokens = token;
		tail = *tokens;
		tail->prev = NULL;
	}
	else
	{
		if (!token)
		{
			tail->next = *tokens;
			(*tokens)->prev = tail;
		}
		else
		{
			tail->next = token;
			tail->next->prev = tail;
			tail = tail->next;
			tail->next = NULL;
		}
	}
}

void	free_tok_list(t_token **token_list)
{
	free_tok_list_rec(*token_list);
	*token_list = NULL;
}

static void	free_tok_list_rec(t_token *token)
{
	if (token->next)
		free_tok_list_rec(token->next);
	free(token);
}
