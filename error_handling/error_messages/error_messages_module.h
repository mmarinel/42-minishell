/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_module.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:23:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 10:00:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_MODULE_H
# define ERROR_MESSAGES_MODULE_H

//* user defined types
# include "../../read/parser/parser_types.h"
# include "../../types.h"

//* user defined exposed functions

//* 		put_error_message cases (main, tokenizer, parser, executor)

void	put_args_error_message(char *arg_found);

void	put_token_not_found_error_message(char *cursor);
void	put_unbalanced_input_error_message(void);

void	put_parser_syntax_error_message(t_parser_status *parser_status);

void	put_cmd_not_found_error_message(char *cmd_name);
void	put_cmd_failed_error_message(char *cmd_name);

void	put_non_existing_error_message(char *file_name);

//*		bultin commands error messages

void	put_cd_path_error_message(void);
void	put_exit_too_many_args_err_msg(void);
void	put_exit_non_numeric_err_msg(void);
void	put_env_opt_err(void);
void	put_env_cmd_err(char *cmd_name);
void	put_pwd_args_error_message(void);

#endif