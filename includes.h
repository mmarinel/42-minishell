/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:40:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/25 07:53:37 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

////////////// 
// // * global variable

// // * PROBABLY I DON'T NEED THIS
// typedef struct s_here_doc
// {
// 	char	*delimiter;
// 	int		fd;
// }	t_here_doc;

// // * PROBABLY I DON'T NEED THIS
// typedef struct s_shell_env
// {
// 	t_here_doc	here_doc;
// }	t_shell_env;

// t_shell_env	*g_shell_env;
///////////////////

// signal handling ...
# include <signal.h>
# include <termios.h>

// errors
# include <errno.h>

// useful macros
# include <limits.h>
// # include <linux/limits.h>

// read, write, file handling ...
# include <unistd.h>
# include <fcntl.h>

// std libs
# include <stdlib.h>
# include <stdio.h>

// readline library
# include <readline/readline.h>
# include <readline/history.h>

// user dfined headers
# include "types.h"
# include "signals/signals.h"
# include "get_next_line/get_next_line.h"
# include "read/read.h"
# include "exit/exit.h"
# include "colors.h"
# include "utils/ft_utils.h"

extern void	rl_replace_line(const char *text, int clear_undo);

#endif
