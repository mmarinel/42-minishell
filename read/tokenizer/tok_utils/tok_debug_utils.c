/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .tok_debug_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:24:02 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:16:52 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

char *tok_to_string(t_token *token)
{
	if (token->token_id == e_CMD_NAME)
		return ("CMD_NAME");
	if (token->token_id == e_CMD_ARG)
		return ("CMD_ARG");
	if (token->token_id == e_IN_FILE_TRUNC)
		return ("IN_FILE_TRUNC");
	if (token->token_id == e_HERE_DOC)
		return ("HERE_DOC");
	if (token->token_id == e_OUT_FILE_TRUNC)
		return ("OUT_FILE_TRUNC");
	if (token->token_id == e_OUT_FILE_APPEND)
		return ("OUT_FILE_APPEND");
	if (token->token_id == e_OPERATOR)
		return ("OPERATOR");
	if (token->token_id == e_ENV_VAR_DECL)
		return ("ENV_VAR_DECL");
	if (token->token_id == e_ENV_VAR_UNSET)
		return ("ENV_VAR_UNSET");
	if (token->token_id == e_PARENTHESIS)
		return ("PARENTHESIS");
	return (NULL);
}
