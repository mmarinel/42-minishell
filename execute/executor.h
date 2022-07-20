/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:45:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:31:49 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

// * standard libraries //
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

// * user defined modules //
# include "../utils/ft_utils.h"
# include "../signals/signals.h"
# include "../read/read_module.h"
# include "../error_handling/error_handling_module.h"
# include "../print/print_module.h"
# include "../exit/exit_module.h"

// * user defined SUBmodules //
# include "builtin/builtin.h"
# include "expander/expander_module.h"
# include "statements/exec_statements.h"
# include "exec_errors/exec_errors.h"
# include "exec_utils/exec_utils.h"

// * user defined types //
# include "executor_types.h"
# include "../read/parser/parser_module.h"
# include "../colors.h"

// * global variable module //
# include "../global.h"

void	execute_rec(t_tree_node *root, int in, int out);

#endif