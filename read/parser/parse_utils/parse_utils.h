/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:56:38 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:13:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

// * standard libraries
# include <stdlib.h>
# include "../../../utils/ft_utils.h"

// * user defined modules
# include "../../../colors.h"
# include "../../../env/env_utils/env_utils.h"
# include "../../tokenizer/tokenizer_module.h"

// * user defined types
# include "../../../types.h"
# include "../parser_types.h"
# include "../../tokenizer/tok_types.h"
# include "../../../global.h"

// * parse utils //

t_tree_node		*new_tree_node(t_tree_node *left, t_node_content *content,
					t_tree_node *right);
void			free_tree(t_tree_node **root_ref);
t_token			*take_next_token(t_parser_status *parser_status);

//* debug //
void			tree_to_string(t_tree_node *root);
void			print_operator(t_tree_node *node);
void			print_simple_command(t_tree_node *node);
void			print_env_statement(t_tree_node *node);

//* parser conditions
t_bool			is_operator_tok(t_token *token);
t_bool			is_closing_paren(t_token *token);
t_bool			is_open_paren(t_token *token);

#endif
