/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:32:58 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 11:01:31 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	put_args_error_message(char *arg_found)
{
	char	*epilogue;

	epilogue = ft_strjoin("\nfound argument: ", arg_found, e_false, e_false);
	put_error_message(
		"minishell: ", "no arguments allowed",
		epilogue,
		e_true
	);
}
