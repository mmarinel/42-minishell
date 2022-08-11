/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_messages.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:36:38 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 10:26:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_exit_too_many_args_err_msg(void)
{
	put_error_message(
		"minishell at execute_exit: ", "too many arguments",
		NULL, e_false
		);
}

void	put_exit_non_numeric_err_msg(void)
{
	put_error_message(
		"minishell at execute_exit: ", "non-numeric argument found",
		NULL, e_false
		);
}
