/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:58:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 11:20:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "error_handling.h"

static void	put_builtin_error(t_err_handl_opcodes error_type, void *argument);

//* end of static declarations


void	put_error(t_err_handl_opcodes error_type, int error_status,
			void *argument)
{
	if (error_type == ARGS_ERROR)
		put_args_error_message(argument);
	if (error_type == TOK_UNBALANCED_ERROR)
		put_unbalanced_input_error_message();
	if (error_type == TOK_NOT_RECOGNIZED_ERROR)
		put_token_not_found_error_message(argument);
	if (error_type == PARSE_ERROR)
		put_parser_syntax_error_message(argument);
	if (error_type == CMD_NOT_FOUND_ERROR)
		put_cmd_not_found_error_message(argument);
	if (error_type == CMD_FAILED_ERROR)
		put_cmd_failed_error_message(argument);
	if (error_type == CD_PATH_ERROR
		|| error_type == EXIT_ARGS_ERROR
		|| error_type == PWD_ARGS_ERROR)
		put_builtin_error(error_type, argument);
	setting_error_code:
	{
		g_env.last_executed_cmd_exit_status = error_status;
	}
}

static void	put_builtin_error(t_err_handl_opcodes error_type, void *argument)
{
	if (error_type == CD_PATH_ERROR)
		put_cd_path_error_message();
	if (error_type == EXIT_ARGS_ERROR)
		put_exit_args_error_message();
	if (error_type == PWD_ARGS_ERROR)
		put_pwd_args_error_message();
	if (argument)
	{}
}
