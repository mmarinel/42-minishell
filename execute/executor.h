/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:45:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:21:40 by mmarinel         ###   ########.fr       */
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
# include "builtin/builtin.h"
# include "statements/exec_statements.h"
# include "exec_errors/exec_errors.h"
# include "exec_utils/exec_utils.h"
# include "../exit/exit_module.h"
# include "../colors.h"
# include "../utils/ft_utils.h"

// * user defined types //
# include "executor_types.h"
# include "../read/parser/parser_module.h"

// * global variable module //
# include "../global.h"

#endif