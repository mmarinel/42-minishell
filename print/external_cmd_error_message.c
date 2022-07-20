/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd_error_message.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:48:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:52:58 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_cmd_not_found_error_message(char *cmd_name)
{
	put_error_message(
		"minishell: command not found ->", cmd_name,
		NULL, e_false);
}

void	put_cmd_failed_error_message(char *cmd_name)
{
	put_error_message(
		"minishell: command failed ->", cmd_name,
		NULL, e_false);
}
