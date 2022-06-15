/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:48:51 by earendil          #+#    #+#             */
/*   Updated: 2022/06/15 22:12:18 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

# include "./read_utils/read_utils.h"

// void *lexer_input_handling(void *arg, char **input_string_ref, int *offset, t_op_code op_code);
// void *lexer_token_handling(void *arg, t_token **cur_token, t_op_code op_code);

static void	*lexer(void *arg, t_op_code op_code)
{
	static char		*__input_string_ref = NULL;
	static int		offset = -1;
	static t_token	*cur_token = NULL;
	
	if (op_code == e_STORE_STR || e_RETURN_CUR_STR || e_ADVANCE_STR)
		return (lexer_input_handling(arg, &__input_string_ref, &offset, op_code));
	else if (op_code == e_STORE_NXT_TOK || op_code == e_RETURN_TOK)
		return (lexer_token_handling(arg, &cur_token, op_code));
	return (NULL);
}

void	tokenizer_feed_input(char **input_str_ref)
{
	if (input_str_ref == NULL)
		return ;
	lexer(input_str_ref, e_STORE_STR);
}

t_token	*get_next_token(void)
{
	return (NULL);
}

void	scan_next_token(void)
{
}