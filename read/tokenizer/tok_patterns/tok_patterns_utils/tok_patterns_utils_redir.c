/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_patterns_utils_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:07:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/24 11:35:27 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns_utils.h"

size_t	scan_var_mode(char *command_line, size_t offset, t_bool *concat_mode)
{
	if (command_line[offset] == '+')
	{
		*concat_mode = e_true;
		return (offset + 1);
	}
	else
	{
		*concat_mode = e_false;
		return (offset);
	}
}
