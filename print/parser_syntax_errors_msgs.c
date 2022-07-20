/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_errors_msgs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:53:49 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:23:30 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_parser_syntax_error_message(t_parser_status *parser_status)
{
	if (parser_status->last_read_tok_pos)
		put_error_message(
			"parser: parse error near token ",
			tok_to_string(parser_status->last_read_token),
			ft_strjoin(
				"at pos ",
				ft_itoa(parser_status->last_read_tok_pos),
				e_false, e_true
			),
			e_true);
}
