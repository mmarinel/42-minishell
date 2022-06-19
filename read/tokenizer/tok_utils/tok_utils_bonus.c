/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:07 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 15:20:20 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

char	*scan_var_name(char *cursor)
{
	if (e_false == ft_is_alpha(*cursor) && *cursor != '_')
		return (NULL);
	cursor++;
	while (*cursor
		&& (char_is_alpha(*cursor)
			|| char_is_digit(*cursor)
			|| *cursor == '_')
		)
		cursor++;
	return (cursor);
}

void	*lexer_input_handling(void *arg, char **input_string_ref,
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

void	*lexer_token_handling(void *arg, t_token **cur_token,
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
