/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_error_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:42:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:44:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_pwd_args_error_message(void)
{
	put_error_message(
		"minishell at execute_pwd: ", "Illegal Arguments found",
		" --no arguments expected", e_false
	);
}
