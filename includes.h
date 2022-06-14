/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:40:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/14 09:28:42 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

// signal handling ...
# include <signal.h>

// errors
# include <errno.h>

// useful macros
# include <limits.h>

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
# include "read/read.h"
# include "colors.h"
# include "types.h"
# include "utils/ft_utils.h"

extern void	rl_replace_line(const char *text, int clear_undo);

#endif
