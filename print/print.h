/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:53:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

//* system libraries
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

//* user defined types
# include "print_types.h"
# include "../colors.h"
# include "../types.h"

//* user defined modules
# include "../utils/ft_utils.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/simple_printf/ft_printf_module.h"
# include "../env/env_module.h"
# include "../read/tokenizer/tokenizer_module.h"
# include "../read/parser/parser_module.h"
// # include // TODO include error handling module !

//* user defined exposed functions

void	put_error_message(char *preamble, char *message, char *epilogue,
			t_bool free_epilogue);

//* 		put_error_message cases (main, tokenizer, parser, executor)

void	put_args_error_message(char *arg_found);

void	put_token_not_found_error_message(char *cursor);
void	put_unbalanced_input_error_message(void);

void	put_parser_syntax_error_message(t_parser_status *parser_status);

void	put_cmd_not_found_error_message(char *cmd_name);
void	put_cmd_failed_error_message(char *cmd_name);

//*		bultin commands error messages

void	put_cd_path_error_message(void);
void	put_exit_args_error_message(void);
void	put_pwd_args_error_message(void);

//* 		stdout byte shift manage

char	*get_stdout_dump_file_name(void);

#endif