/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cases.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:21:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 10:15:26 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CASES_H
# define PARSER_CASES_H

// * user defined module //
# include "../parser.h"

// * end of includes //

	//* atomic expressions
t_tree_node	*parse_atomic_exp(t_parser_status *parser_status);

	//* cmd list
t_tree_node	*parse_cmd_list(t_parser_status *parser_status);

	//* simple statement
t_tree_node		*parse_statement(t_token *token);
t_node_content	*parse_operator(t_token *token);
t_node_content	*parse_simple_command(t_token *token,
					t_node_content *node_content);
t_node_content	*parse_env_statement(t_token *token,
					t_node_content *node_content);
void			parse_redir(t_node_content *node_content,
					char *file_name, t_token_id in_out);

// //* utils
// void	parser_initialize(t_parser_status *parser_status);

#endif