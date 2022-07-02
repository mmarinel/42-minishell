/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atomic_exp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:19:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 14:29:20 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases_init.h"

t_token	*atomic_exp_parsing_init(t_parser_status *parser_status)
{
	t_token	*token;

	if (parser_status->status == ERROR)
		return (NULL);
	token = take_next_token(parser_status);
	if (!token)
		return (NULL);
	if (
		token->token_id == e_OPERATOR
		||
		(
			token->token_id == e_PARENTHESIS
			&& *((char *)token->token_val) != '('
		)
	)
	{
		set_error(&(parser_status->status));
		return (NULL);
	}
	return (token);
}
