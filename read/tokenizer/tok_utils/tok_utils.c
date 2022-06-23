/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 17:22:19 by mmarinel         ###   ########.fr       */
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

size_t	mini_next_word_len(char *command_line, size_t offset)
{
	size_t	len_word;

	len_word = 0;
	while (e_false == bash_control_character
		(
			command_line[offset + len_word]
		)
		&& command_line[offset + len_word]
	)
		len_word++;
	return (len_word);
}

/**
 * @brief this function adds the given token to the end of the current
 * list of tokens (circular list only on prev pointers)
 * 
 * @param token_list the address of the first element in the list
 * @param token the next token to store or NULL to close the list
 */
void	tok_add_back(t_token **token_list, t_token *token)
{
	static t_token	*tail = NULL;

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
		id = BOLDGREEN "CMD_NAME" RESET;
	if (token->token_id == e_CMD_ARG)
		id = BOLDYELLOW "CMD_ARG" RESET;
	if (token->token_id == e_IN_FILE)
		id = BOLDBLUE "IN_FILE" RESET;
	if (token->token_id == e_OUT_FILE)
		id = BOLDBLUE "OUT_FILE" RESET;
	if (token->token_id == e_OPERATOR)
		id = BOLDRED "OPERATOR" RESET;
	if (token->token_id == e_ENV_VAR_DECL)
		id = BOLDMAGENTA "ENV_VAR_ASSIGNATION" RESET;
	if (token->token_id == e_PARENTHESIS)
		id = BOLDCYAN "PARENTHESIS" RESET;
	printf("%s ", id);
}
