/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:45:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 11:29:35 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// *system libraries //
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

// * user defined submodules //
# include "signals/signal_module.h"
# include "read/read_module.h"
# include "execute/executor_module.h"
# include "env/env_module.h"
# include "utils/ft_utils.h"

// * user defined types
# include "global.h"
# include "types.h"
# include "colors.h"

#endif
