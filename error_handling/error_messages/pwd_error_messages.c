/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_error_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:42:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 10:27:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_pwd_args_error_message(void)
{
	put_error_message(
		"minishell at execute_pwd: ", "Illegal Arguments found",
		" --no arguments expected", e_false
		);
}
