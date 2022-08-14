/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:45:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/14 19:40:49 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// *system libraries //
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

// * user defined submodules //
# include "utils/ft_utils.h"
# include "env/env_module.h"
# include "signals/signal_module.h"
# include "read/read_module.h"
# include "execute/executor_module.h"
# include "error_handling/error_handling_module.h"
# include "exit/exit_module.h"

// * user defined types
# include "global.h"
# include "types.h"
# include "colors.h"

#endif
