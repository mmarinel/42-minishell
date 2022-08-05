/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_existing_file_error_msg.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:48:19 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 10:51:01 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"

void	put_non_existing_error_message(char *file_name)
{
	if (file_name)
		;
	perror("minishell: ");
}
