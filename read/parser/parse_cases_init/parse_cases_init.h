/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cases_init.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:21:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 14:47:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CASES_UTILS_H
# define PARSER_CASES_UTILS_H

// * user defined module //
# include "../parser.h"

// * end of includes //

t_token	*atomic_exp_parsing_init(t_parser_status *parser_status);
t_token	*cmd_list_parsing_init(t_parser_status *parser_status);
void	parser_initialize(t_parser_status *parser_status);
t_token	*parse_statement_init(t_token *token,
			t_node_content **node_content_ref);

#endif