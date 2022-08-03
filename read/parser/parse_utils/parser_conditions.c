/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_conditions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:21:51 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 10:16:26 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

t_bool	is_operator_tok(t_token *token)
{
	return (token->token_id == e_OPERATOR);
}

t_bool	is_closing_paren(t_token *token)
{
	return 
	(
		token->token_id == e_PARENTHESIS
		&&
		*((char *)token->token_val) == ')'
	);
}

t_bool	is_open_paren(t_token *token)
{
	return 
	(
		token->token_id == e_PARENTHESIS
		&&
		*((char *)token->token_val) == '('
	);
}
