/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_statements.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:05:04 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:07:10 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STATEMENTS_H
# define EXEC_STATEMENTS_H

# include "../executor.h"

// * composed statements //
void	execute_pipe_statement(t_tree_node *root, int in, int out);
void	execute_and_statement(t_tree_node *root, int in, int out);
void	execute_or_statement(t_tree_node *root, int in, int out);

// * simple statements //
void	execute_simple_statement(t_tree_node *root, int in, int out);

#endif