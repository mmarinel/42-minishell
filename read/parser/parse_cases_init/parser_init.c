/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:29:47 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 14:30:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases_init.h"

void	parser_initialize(t_parser_status *parser_status)
{
	parser_status->last_read_token = NULL;
	parser_status->status = OK;
	parser_status->open.double_qquotes = 0;
	parser_status->open.quotes = 0;
	parser_status->open.parenthesis = 0;
}
