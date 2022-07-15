/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 18:03:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../types.h"

//* user defined modules
# include "../libft/libft.h"

//* useful macros
# include <limits.h>

//* read, write, file handling ...
# include <unistd.h>
# include <fcntl.h>

//* std libs
# include <stdlib.h>
# include <stdio.h>

//* includes end //


// * shell utils

void			set_error(t_status *status);
t_bool			ft_pending_pipe(char *command);
t_bool			ft_pending_logical_op(char *command);
t_bool			bash_control_character(char c);
t_bool			ft_is_quote(char c);
t_bool			bash_cmd_separator(char c);
t_bool			redirect_char(char c);
t_bool			asked_for_termination(char	*command);
void			close_pipe(int pipe_[]);
int				ft_open_file(char *file, unsigned long long flags, int mode);

#endif