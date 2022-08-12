/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_statements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:10:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 15:49:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_STATEMENTS_H
# define SIMPLE_STATEMENTS_H

# include "../../executor_types.h"
# include "../exec_statements.h"
# include "../../expander/expander_module.h"
# include "../../../env/env_module.h"
//* redirections

t_status	external_handle_redirs(t_redirection redir, int cur_in_out,
				int std_in_out, t_bool input_redir_case);
t_status	builtin_handle_redirs(t_redirection redir, int cur_in_out,
				int std_in_out, t_bool input_redir_case);
t_status	open_paren_node_redirs(int *in, int *out,
				t_node_content *parenthesis_node);

void		execute_external_simple_cmd(t_tree_node *root, int in, int out);

void		execute_env_statement(t_env_decl_node env_statement);
void		execute_redir_only_statement(t_tree_node *root,
				int in, int out);
void		execute_cmd_builtin(t_simple_command_node simple_cmd);

#endif
