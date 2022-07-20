/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_module.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:58:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_MODULE_H
# define PRINT_MODULE_H

//* user defined types
# include "print_types.h"
# include "../read/parser/parser_types.h"
# include "../types.h"

//* user defined exposed functions

size_t	printer(t_print_opcode opcode);

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