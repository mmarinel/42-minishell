/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_syntax_errors_msgs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:36:51 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 10:27:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_unbalanced_input_error_message(void)
{
	put_error_message("Syntax Error: ",
		"unbalanced input string",
		"you have at least one pending quote or parenthesis",
		e_false
		);
}

void	put_token_not_found_error_message(char *cursor)
{
	put_error_message("Syntax Error: ",
		"token not recognized",
		ft_strjoin("near ...", cursor, e_false, e_false),
		e_true
		);
}
