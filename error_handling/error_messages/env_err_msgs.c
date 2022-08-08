/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_err_msgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:28:28 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 09:51:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_env_opt_err(void)
{
	put_error_message(
		"minishell at execute_env: ", "Illegal arguments or option found",
		NULL, e_false
	);
}

void	put_env_cmd_err(char *cmd_name)
{
	put_error_message(
		"minishell at execute_env: ", "cmd not found",
		cmd_name, e_false
	);
}
