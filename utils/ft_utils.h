/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 19:12:12 by mmarinel         ###   ########.fr       */
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

size_t			bash_next_word_len(char *command_line, size_t offset);
size_t			bash_next_string_len(char *str, size_t offset);
t_bool			is_env_var_name(char *str);
t_bool			bash_word_is_empty(char *command);
t_bool			command_is_empty(char *command);
void			set_error(t_status *status);
t_bool			ft_pending_pipe(char *command);
t_bool			ft_pending_logical_op(char *command);
t_bool			bash_control_character(char c);
t_bool			ft_is_quote(char c);
t_bool			bash_cmd_separator(char c);
t_bool			redirect_char(char c);
t_bool			asked_for_termination(char	*command);
void			clone_pipe(int target[2], int clone[2]);
void			close_pipe(int pipe_[]);
int				ft_open(char *file_name,
					unsigned long long flags, int mode,
					t_bool free_file_name);
int				ft_unlink(char *file_name, t_bool free_file_name);

#endif