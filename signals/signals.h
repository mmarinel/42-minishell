/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 07:51:39 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 15:04:56 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// * system libraries //
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>

// * user defined modules //
# include "../read/prompt/prompt_module.h"
# include "../env/env_module.h"
# include "../libft/libft.h"
# include "../global.h"
# include "../read/prompt/here_doc/here_doc_module.h"

// * user defined types //
# include "signal_types.h"

extern void	rl_replace_line(const char *text, int clear_undo);

/**
 * @brief handler for all
 * 
 * @param signum 
 */
void	sig_handler(int signum);
void	sig_ign(int signum);
void	sig_handling_set(t_sig_handling_opcode opcode);
void	shell_executor_handler(int signum);
void	line_completion_prompt_sig_handler(int signum);

#endif
