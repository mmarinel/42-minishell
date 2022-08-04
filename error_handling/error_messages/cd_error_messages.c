/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:28:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 16:09:24 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_cd_path_error_message(void)
{
	put_error_message(
		"minishell at execute cd: ", "HOME not set",
		NULL, e_false
	);
}
