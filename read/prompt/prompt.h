/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:43:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 13:19:10 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

//* standard libraries
# include <unistd.h>
# include <stdlib.h>

//* user defined types
# include "prompt_types.h"
# include "../../types.h"

//* user defined 
# include "../../colors.h"
# include "../../utils/ft_utils.h"
# include "../../env/env_module.h"

//* SUBMODULES //
# include "line_continuation_prompt/line_continuation_prompt.h"
# include "here_doc/here_doc_module.h"
# include "prompt_utils/prompt_utils.h"
# include "../../signals/signals.h"
# include "../../utils/ft_utils.h"

//* readline //
# include <readline/readline.h>
# include <readline/history.h>

extern void	rl_replace_line(const char *text, int clear_undo);

// * includes end //

char		*prompt_complete_line(char *command);

#endif