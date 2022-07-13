/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_statements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:10:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 16:51:07 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_STATEMENTS_H
# define SIMPLE_STATEMENTS_H

# include "../../executor_types.h"
# include "../exec_statements.h"
# include "../../expander/expander_module.h"
# include "../../../env/env_module.h"

void	execute_simple_cmd(t_tree_node *root, int in, int out);
void	execute_builtin(t_tree_node *cmd, int in, int out);
void	execute_redir_only_statement(t_tree_node *root, int in, int out);

#endif
