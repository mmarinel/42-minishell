/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:45:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/13 14:49:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// signal handling ...
#include <signal.h>

// read, write, file handling ...
#include <unistd.h>
#include <fcntl.h>

// std libs
#include <stdlib.h>
#include <stdio.h>

// readline library
#include <readline/readline.h>
#include <readline/history.h>
extern void	rl_replace_line(const char *text, int clear_undo);

// user includes
#include "colors.h"


void	*ft_malloc(size_t size);

#endif
