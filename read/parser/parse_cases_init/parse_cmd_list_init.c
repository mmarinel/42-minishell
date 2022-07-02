/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:23:44 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 14:29:27 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases_init.h"

t_token	*cmd_list_parsing_init(t_parser_status *parser_status)
{
	t_token	*token;

	if (parser_status->status == ERROR)
		return (NULL);
	token = take_next_token(parser_status);
	if (!token)
		return (NULL);
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == ')')
	{
		if (parser_status->open.parenthesis == 0)
			set_error(&(parser_status->status));
		else
			parser_status->open.parenthesis -= 1;
		return (NULL);
	}
	return (token);
}
