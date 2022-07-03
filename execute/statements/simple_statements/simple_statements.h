/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_statements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:10:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 12:34:04 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_STATEMENTS_H
# define SIMPLE_STATEMENTS_H

# include "../../executor_types.h"
# include "../exec_statements.h"

void	execute_simple_cmd(t_tree_node *root, int in, int out);
t_bool	execute_builtin(t_simple_command_node cmd, int in, int out);
void	execute_redir_only_statement(t_tree_node *root, int in, int out);

#endif
