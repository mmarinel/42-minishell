/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_scan_loops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:07:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/29 09:09:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_patterns.h"

size_t	scan_redirs(char *command_line, size_t offset, t_token **token_list)
{
	size_t	new_offset;

	new_offset = scan_inout_file(command_line, offset, token_list);
	while (new_offset > offset)
	{
		offset = new_offset;
		new_offset =  scan_inout_file(command_line, new_offset, token_list);
	}
	return (new_offset);
}

size_t	scan_parenthesis(char *command_line, size_t offset, t_token **token_list)
{
	size_t	new_offset;

	new_offset = scan_single_par(command_line, offset, token_list);
	while (new_offset > offset)
	{
		offset = new_offset;
		new_offset =  scan_single_par(command_line, new_offset, token_list);
	}
	return (new_offset);
}
