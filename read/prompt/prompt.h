/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:43:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/11 16:38:08 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H


// * standard libraries
# include <unistd.h>
# include <stdlib.h>

// * user defined types
# include "prompt_types.h"
# include "../../types.h"

// * user defined 
# include "../../colors.h"
# include "../../utils/ft_utils.h"
# include "../../env/env_module.h"

// * SUBMODULES //
# include "line_continuation_prompt/line_continuation_prompt.h"
# include "prompt_utils/prompt_utils.h"
# include "../../signals/signals.h"

// * readline //
# include <readline/readline.h>
# include <readline/history.h>

extern void	rl_replace_line(const char *text, int clear_undo);


// * includes end //


// TODO :-> return EXIT CODE 258 for ctrl + D
// TODO :-> while trying to complete line (exit/errors module)
char	*prompt_complete_line(char *command);


#endif