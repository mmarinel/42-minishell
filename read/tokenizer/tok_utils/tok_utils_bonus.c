/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 09:09:57 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

static void	*lexer_input_handling(void *arg, char **input_string_ref,
			int *offset, t_op_code op_code)
{
	if (op_code == e_STORE_STR && *offset > -1)
	{
		*input_string_ref = (char *)arg;
		*offset = 0;
	}
	else if (op_code == e_ADVANCE_STR && *offset > -1)
	{
		*offset = range_spill(
				*offset + *((int *)arg),
				ft_strlen(*input_string_ref),
				0, -1
				);
		if (*offset == -1)
			free(*input_string_ref);
	}
	else if (op_code == e_RETURN_CUR_STR && *offset > -1)
	{
		return (*input_string_ref + *offset);
	}
	return (NULL);
}

static void	*lexer_token_handling(void *arg, t_token **cur_token,
			t_op_code op_code)
{
	if (op_code == e_STORE_NXT_TOK)
	{
		ft_free(*cur_token);
		*cur_token = (t_token *)arg;
		return (NULL);
	}
	else if (op_code == e_RETURN_TOK)
	{
		return (*cur_token);
	}
	return (NULL);
}

// ! to DECOMMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void	*lexer(void *arg, t_op_code op_code)
{
	static char		*__input_string = NULL;
	static int		offset = -1;
	static t_token	*cur_token = NULL;

	if (op_code == e_CLEAN)
	{
		ft_free(__input_string);
		__input_string = NULL;
		ft_free(cur_token);
		cur_token = NULL;
		offset = -1;
	}
	if (op_code == e_STORE_STR || op_code == e_RETURN_CUR_STR
		|| op_code == e_ADVANCE_STR)
		return (lexer_input_handling(arg,
				&__input_string, &offset, op_code));
	else if (op_code == e_STORE_NXT_TOK || op_code == e_RETURN_TOK)
		return (lexer_token_handling(arg,
				&cur_token, op_code));
	return (NULL);
}
