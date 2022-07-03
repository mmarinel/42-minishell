/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_statements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:10:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:18:38 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_STATEMENTS_H
# define SIMPLE_STATEMENTS_H

# include "../exec_statements.h"

void	execute_simple_cmd(t_tree_node *root, int in, int out);
void	execute_redir_only_statement(t_tree_node *root, int in, int out);

#endif
